#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/tm4c1294ncpdt.h" // CMSIS-Core
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h" 
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/uartstdio.h"
#include "driverlib/pin_map.h"

//#define BASE_FREQUENCY 24000000
#define BASE_FREQUENCY 24000000
#define FREQUENCY_MEGA 24
#define SAMPLE_SIZE 11


void onEdgeDown(void);
void onEdgeUp(void);

void initUART(void) { 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, 16000000);
    UARTprintf("UART started\n");
}

void setClockFrequency(int clockFrequency){

  uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                              SYSCTL_OSC_MAIN |
                                              SYSCTL_USE_PLL |
                                              SYSCTL_CFG_VCO_480),
                                              clockFrequency);
}

void initGPIO(){

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK));
  
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  
    // Interrupt setup
    //GPIOIntDisable(GPIO_PORTK_BASE, GPIO_PIN_7);        // Disable interrupt for PF4 (in case it was enabled)
    //GPIOIntClear(GPIO_PORTK_BASE, GPIO_PIN_7);          // Clear pending interrupts for PF4
    //GPIOIntRegister(GPIO_PORTK_BASE, onEdgeDown);       // Register our handler function for port F
   // GPIOIntTypeSet(GPIO_PORTK_BASE, GPIO_PIN_7,
      //  GPIO_FALLING_EDGE);                             // Configure PK4 for falling edge trigger
   // GPIOIntRegister(GPIO_PORTK_BASE, onEdgeUp);         // Register our handler function for port F
   // GPIOIntTypeSet(GPIO_PORTK_BASE, GPIO_PIN_7,
        //GPIO_RISING_EDGE);                              // Configure PF4 for falling edge trigger
   // GPIOIntEnable(GPIO_PORTK_BASE, GPIO_PIN_7);         // Enable interrupt for PF4
 
}


//When the timer captures a event it stores the current counter value in GPTMTnR
//and GPTMTnPSN registers and it stays there until other event changes the value.
void initTimers(){
  
  /////Configurações do Timer0 -------------------------------------------------
  // Enable and configure Timer0 peripheral.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  // Wait for the Timer0 module to be ready.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}

  // Configure TimerA and B 
  TimerConfigure(TIMER0_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP | TIMER_CFG_B_CAP_TIME_UP));
  // Set both timers to start at zero
  //TimerLoadSet(TIMER0_BASE, TIMER_BOTH, 0x0);
  // TimerA triggers on positive edge, TimerB triggers on negative edge
  TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
  TimerControlEvent(TIMER0_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
  
  // Enable the timers.
  //TimerEnable(TIMER0_BASE, TIMER_BOTH); <--Tirei daqui pra testar uma coisa
  
  /////Configurações do Pino D0 e D1 -------------------------------------------
  //Enable para os periféricos
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  
  GPIOPinConfigure(GPIO_PD0_T0CCP0);
  GPIOPinConfigure(GPIO_PD1_T0CCP1);
  GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_0);
  GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_1);
  
  // Interrupt setup GPIO -> Funciona, sinal PWM apenas no D0
  //GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_0);        // Disable interrupt for PD0
  //GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_0);          // Clear pending interrupts for PD
  //GPIOIntRegister(GPIO_PORTD_BASE, onEdgeDown);       // Register our handler function for port D0
  //GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0,
  //GPIO_FALLING_EDGE);                             // Configure PK4 for falling edge trigger
  //GPIOIntRegister(GPIO_PORTD_BASE, onEdgeUp);         // Register our handler function for port D
  //GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0,
  //GPIO_RISING_EDGE);                              // Configure PF4 for falling edge trigger
  //GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_0);         // Enable interrupt for PF4

  //Interrup setup Timer -> Timer A no D0 e TimerB no D1
  //Registers a interrupt function to be called when timer b hits a neg edge event
    TimerIntRegister(TIMER0_BASE, TIMER_A, onEdgeUp); 
    TimerIntRegister(TIMER0_BASE, TIMER_B, onEdgeDown); 
    // Makes sure the interrupt is cleared
    TimerIntClear(TIMER0_BASE, TIMER_CAPA_EVENT);
    TimerIntClear(TIMER0_BASE, TIMER_CAPB_EVENT);
    // Enable the indicated timer interrupt source.
    TimerIntEnable(TIMER0_BASE, TIMER_CAPA_EVENT);
    TimerIntEnable(TIMER0_BASE, TIMER_CAPB_EVENT);
    // The specified interrupt is enabled in the interrupt controller.
    //IntEnable(INT_TIMER0A);
    //IntEnable(INT_TIMER0B);
    
    // Enable the timers.
    TimerEnable(TIMER0_BASE, TIMER_BOTH);
    UARTprintf("TimerA %d TimerB: %d  \n", TimerValueGet(TIMER0_BASE, TIMER_A), TimerValueGet(TIMER0_BASE, TIMER_B));
 
}

int a = 0;
int b = 0; //depois isso evolui pros arrays que usaremos pra capturar amostras 
int size = 0;
uint32_t  start = 0, end = 0, length = 0;

int sample_high[SAMPLE_SIZE], sample_low[SAMPLE_SIZE];   
int high_index=0;
int low_index=0; 


//E quando o valor dos contadores 
void onEdgeDown(void) {

  if(high_index<SAMPLE_SIZE){
   sample_high[high_index] =  abs(TimerValueGet(TIMER0_BASE, TIMER_A) -  TimerValueGet(TIMER0_BASE, TIMER_B));
   high_index++;
  }
   TimerIntClear(TIMER0_BASE, TIMER_CAPB_EVENT); 
}

void onEdgeUp(void) {
   
  if(low_index<SAMPLE_SIZE){
   sample_low[low_index] =  abs(TimerValueGet(TIMER0_BASE, TIMER_A) -  TimerValueGet(TIMER0_BASE, TIMER_B));
   low_index++;
  }
  TimerIntClear(TIMER0_BASE, TIMER_CAPA_EVENT);
}

void main(void){
  
  setClockFrequency(BASE_FREQUENCY);
  initGPIO();
  initUART();
  initTimers();

  //Captura as amostras
  while(high_index<SAMPLE_SIZE && low_index<SAMPLE_SIZE){
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_7, GPIO_PIN_7);
    SysCtlDelay(100);
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_7, 0);
    SysCtlDelay(300);
  }

  //Imprime os valores
  for (int i = 1; i<SAMPLE_SIZE; i++){
    UARTprintf("Amostra: %d Tempo em alta: %d us Tempo em baixa: %d us ciclo: %d  \n", i, (sample_high[i]/FREQUENCY_MEGA), (sample_low[i]/FREQUENCY_MEGA), sample_high[i]*100/(sample_high[i]+sample_low[i]));
  }
  
  while(1);
} 
