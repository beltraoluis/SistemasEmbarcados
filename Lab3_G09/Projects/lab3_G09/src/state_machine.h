/***
* S12_G09_Lab3
* Laboratório 3 - Sistemas Embarcados
* André Luiz Rodrigues dos Santos
* Luís Henrique Beltrão Santana
* Lucas Silvestre Kloss Teles
**/

#include <string.h>

#include "elevator.h"

#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#define STOPPED_OPEN_DOORS 1
#define STOPPED_CLOSE_DOORS 2
#define GOING_UP 3
#define GOING_DOWN 4

void controlTask(void *arg0);
void changeState(Elevator *elev, char command[], char * str);

#endif