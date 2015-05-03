#include "recharged.h"


list_head_t* createList() {
    return malloc(sizeof(list_head_t));
}


void addListElement(list_head_t* list, list_object_t* element) {
    element->next = NULL;
    element->previous = list->last;
}
