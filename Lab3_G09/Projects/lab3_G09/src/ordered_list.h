/***
* S12_G09_Lab3
* Laboratório 3 - Sistemas Embarcados
* André Luiz Rodrigues dos Santos
* Luís Henrique Beltrão Santana
* Lucas Silvestre Kloss Teles
**/

#ifndef BELTRAOLUIS_C_ORDERED_LIST_H
#define BELTRAOLUIS_C_ORDERED_LIST_H

typedef struct char_node{
    struct char_node *previous;
    struct char_node *next;
    char data;
} char_node;

int char_set_size(char_node *list);
void char_set_add(char_node **list, char data);
char char_set_remove(char_node **list);

#endif //BELTRAOLUIS_C_ORDERED_LIST_H
