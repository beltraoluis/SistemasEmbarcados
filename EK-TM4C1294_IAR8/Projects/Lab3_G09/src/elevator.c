#include "elevator.h"

int pos = 0;
char levelE = 'x';
char levelC = 'x';
char levelD = 'x';

void rule(char param[], Elevator elev){
  char command[BUFFER];
  switch(param[1]){
     case 'I':
      if(elev.level != param[2]){
        //todo: proteger com mutex
        char* dest = turnLightOn(param);
        queue_append((queue_t **)&elev.commands, (queue_t *)dest);
        dest = closeDoor(param);
        queue_append((queue_t **)&elev.commands, (queue_t *)dest);
        //            controlList[pos++] = turnLightOn(param); // acende a luz do painel interno
        //            controlList[pos++] = closeDoor(param);   // fecha a porta
        if(elev.level != 'p' && (int) elev.level < (int) param[2]){
          dest = goUp(param);
          queue_append((queue_t **)&elev.commands, (queue_t *)dest);
          //              controlList[pos++] = goUp(param);    // subir
        } else if(elev.level != 'a' && (int) elev.level > (int) param[2]){
          dest = goDown(param);
          queue_append((queue_t **)&elev.commands, (queue_t *)dest);
          //              controlList[pos++] = goDown(param);    // descer
        }
      }
    break;
     case 'E':
    break;
     default: 
    break;
  }
}

char* goUp(char elev[]) {
  char dest[50];
  char elem[2] = elev[0];
  strcpy(dest, "going up ");
  strcat(dest, elem);
  strcat(dest, " \n");
  printf("%s", dest);  
  char command[BUFFER];
  command[0] = elev[0];  // qual elevador
  command[1] = 's';
  command[2] = '\r';
  command[3] = '\0';
  return command;
}

char* goDown(char elev[]) {
  char dest[50];
  char elem[2] = elev[0];
  strcpy(dest, "going down ");
  strcat(dest, elem);
  strcat(dest, " \n");
  printf("%s", dest);  
  char command[BUFFER];
  command[0] = elev[0];  // qual elevador
  command[1] = 'd';
  command[2] = '\r';
  command[3] = '\0';
  return command;
}

char* stop(char elev[]) {
  char dest[50];
  char elem[2] = elev[0];
  strcpy(dest, "stopping ");
  strcat(dest, elem);
  strcat(dest, " \n");
  printf("%s", dest);
  char command[BUFFER];
  command[0] = elev[0];  // qual elevador
  command[1] = 'p';
  command[2] = '\r';
  command[3] = '\0';
  return command;
}

char* closeDoor(char elev[]) {
  char dest[50];
  char elem[2] = elev[0];
  strcpy(dest, "closing door ");
  strcat(dest, elem);
  strcat(dest, " \n");
  printf("%s", dest);    
  char command[BUFFER];
  command[0] = elev[0];  // qual elevador
  command[1] = 'f';
  command[2] = '\r';
  command[3] = '\0';
  return command;
}

char* openDoor(char elev[]) {
  char dest[50];
  char elem[2] = elev[0];
  strcpy(dest, "opening door ");
  strcat(dest, elem);
  strcat(dest, " \n");
  printf("%s", dest);    
  char command[BUFFER];
  command[0] = elev[0];  // qual elevador
  command[1] = 'a';
  command[2] = '\r';
  command[3] = '\0';
  return command;
}

char* turnLightOn(char param[]) {
  char dest[50];
  char elem[2] = param[0];
  strcpy(dest, "turning light on ");
  strcat(dest, elem);
  strcat(dest, " \n");
  printf("%s", dest);    
  char command[BUFFER];
  command[0] = param[0];  // qual elevador
  command[1] = 'L';       // acende a luz no simulador
  command[2] = param[2];  // qual andar
  command[3] = '\r';
  command[4] = '\0';
  return command;
}