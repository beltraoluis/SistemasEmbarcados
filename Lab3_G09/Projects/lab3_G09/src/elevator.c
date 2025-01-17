/***
* S12_G09_Lab3
* Laboratório 3 - Sistemas Embarcados
* André Luiz Rodrigues dos Santos
* Luís Henrique Beltrão Santana
* Lucas Silvestre Kloss Teles
**/

#include "elevator.h"
#include "state_machine.h"
#include <stdlib.h>

int pos = 0;

void goUp(char elev[], char * str) {
  char command[BUFFER] = "xs\r\0";
  command[0] = elev[0];  // qual elevador
  strcpy(str, command);
}

void goDown(char elev[], char * str) {
  char command[BUFFER] = "xd\r\0";
  command[0] = elev[0];  // qual elevador
  strcpy(str, command);
}

void stop(char elev[], char * str) {
  char command[BUFFER] = "xp\r\0";
  command[0] = elev[0];  // qual elevador
  strcpy(str, command);
}

void closeDoor(char elev[], char * str) {   
  char command[BUFFER] = "xf\r\0";
  command[0] = elev[0];  // qual elevador
  strcpy(str, command);
}

void openDoor(char elev[], char * str) {  
  char command[BUFFER] = "xa\r\0";
  command[0] = elev[0];  // qual elevador
  strcpy(str, command);
}

void turnLightOn(char param[], char * str) {
  char command[BUFFER] = "xLx\r\0";
  command[0] = param[0];  // qual elevador
  command[2] = param[2];  // qual andar
  strcpy(str, command);
}

void turnLightOff(char param[], char * str) {
  char command[BUFFER] = "xDx\r\0";
  command[0] = param[0];  // qual elevador
  command[2] = param[2];  // qual andar
  strcpy(str, command);
}

char strMap(char *str){
  if(str[2] == '\0'){
    switch(str[1]){
      case '0': return 'a';
      case '1': return 'b';
      case '2': return 'c';
      case '3': return 'd';
      case '4': return 'e';
      case '5': return 'f';
      case '6': return 'g';
      case '7': return 'h';
      case '8': return 'i';
      case '9': return 'j';
      default: return '\0';
    }
  } else {
    switch(str[2]){
      case '0': return 'k';
      case '1': return 'l';
      case '2': return 'm';
      case '3': return 'n';
      case '4': return 'o';
      case '5': return 'p';
      default: return '\0';
    }
  }
}

void addElementToQueue(Elevator *elev, char elem) {
  char tmp[15];
  if ((int)elev->level < (int)elem) {
     for (uint8_t i = 0; i < 15 ; i++) {
      if (elev->upNextLevel[i] == 'r') {
        elev->upNextLevel[i] = elem;
        break;
      }
    }
//    strncpy(tmp, elev->upNextLevel, 15);
//    qsort(tmp, 15, sizeof(char), cmpfunc);
//    for (uint8_t i = 0; i < 15 ; i++) {
//      elev->upNextLevel[i] = tmp[i];
//    }
  } else {
    for (uint8_t i = 0; i < 15 ; i++) {
      if (elev->downNextLevel[i] == 'r') {
        elev->downNextLevel[i] = elem;
        break;
      }
    }
    //todo: ordenar array
  }
}

void removeFirstElementFromQueue(Elevator *elev) {
  switch(elev->prevMovState){
   case GOING_UP:
      for (uint8_t i = 0; i < 15; i++) {
        elev->upNextLevel[i] = elev->upNextLevel[i+1];
      }
      elev->upNextLevel[14] = 'r'; 
   break;
     case GOING_DOWN:   
      for (uint8_t i = 0; i < 15; i++) {
        elev->downNextLevel[i] = elev->downNextLevel[i+1];
      }
      elev->downNextLevel[14] = 'r';  
   break;
   default: break;
  }
}

int cmpfunc (const void * a, const void * b) {
   return ( *(char*)a - *(char*)b );
}