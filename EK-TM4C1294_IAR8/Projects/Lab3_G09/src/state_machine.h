/***
 * S12_G09_Lab3
 * Laborat�rio 3 - Sistemas Embarcados
 * Andr� Luiz Rodrigues dos Santos
 * Lu�s Henrique Beltr�o Santana
 * Lucas Silvestre Kloss Teles
**/

#include "elevator.h"

#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#define STOPPED_OPEN_DOORS 1
#define STOPPED_CLOSE_DOORS 2
#define GOING_UP 3
#define GOING_DOWN 4

void changeState(Elevator elev, char[] command);

#endif