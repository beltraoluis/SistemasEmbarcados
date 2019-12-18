/***
* S12_G09_Lab3
* Laboratório 3 - Sistemas Embarcados
* André Luiz Rodrigues dos Santos
* Luís Henrique Beltrão Santana
* Lucas Silvestre Kloss Teles
**/


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ordered_list.h"

int char_set_size(char_node *list){
    int i = 0;
    if(list != NULL){
        char_node *tmp = list;
        i++; /// correct counting by add 1
        while(tmp->next != list){
            i++;
            tmp = tmp->next;
        }
    }
    return i;
}

void char_set_add(char_node **list, char data){
    char_node *element = malloc(sizeof(char_node));
    element->next = NULL;
    element->previous = NULL;
    element->data = data;
    char_node *tmp = NULL;
    /// if list isn't NULL
    if (list != NULL) {
        /// if element isn't in an other list
        if(element->previous == NULL && element->next == NULL) {
            if (*list != NULL) {
                tmp = *list;
                while (tmp->next != *list) {
                    if(((int)(tmp->next->data)) >= ((int)(element->data))) break;
                    tmp = tmp->next;
                }
                if(tmp->data != element->data) {
                    element->next = tmp->next;
                    tmp->next = element;
                    element->previous = tmp;
                    (element->next)->previous = element;
                }
            }
            else {
                element->next = element;
                element->previous = element;
                *list = element;
            }
        }
    }
}

char char_set_remove(char_node **list){
    bool onList = false;
    /// if list isn't NULL
    if(list != NULL){
        ///  if list isn't void
        if(*list != NULL){
            char_node *tmp = *list;
            /// if element is on the list
            if(char_set_size(*list) > 0){
                /// if is single item 
                if((*list)->next == *list){
                    *list = NULL;
                }
                    /// if isn't single item
                else{
                    /// set pointers
                    (*list)->previous->next = (*list)->next;
                    (*list)->next->previous = (*list)->previous;
                    *list =  (*list)->next;
                }
                tmp->previous = NULL;
                tmp->next = NULL;
                char data = tmp->data;
                free(tmp);
                return data;
            }
        }
    }
    return '\0';
}