/***
* S12_G09_Lab3
* Laborat�rio 3 - Sistemas Embarcados
* Andr� Luiz Rodrigues dos Santos
* Lu�s Henrique Beltr�o Santana
* Lucas Silvestre Kloss Teles
**/

#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"

void sendString(char string[]);
#endif
