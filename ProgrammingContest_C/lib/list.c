#include <stdlib.h>

/*
 *   ----    ←    ----    ←    ----   ←    ----       ----
 *  |NULL|       |head|       |node|      |tail|     |NULL|
 *   ----         ----    ⇨    ----   ⇨    ----   ⇨   ----
 */

typedef struct DOUBLYLINKEDLIST{
    struct DOUBLYLINKEDLIST *  prev;
    struct DOUBLYLINKEDLIST *  next;
    int value;
}DOUBLYLINKEDLIST;


void insert(DOUBLYLINKEDLIST **head, DOUBLYLINKEDLIST **tail, int x){
    DOUBLYLINKEDLIST * inserted = (DOUBLYLINKEDLIST *)malloc(sizeof(DOUBLYLINKEDLIST));
    inserted->value = x;
    
    if(*head == NULL && *tail == NULL){
        inserted->prev = NULL;
        inserted->next = NULL;
        *head = inserted;
        *tail = inserted;
    }
    else
    {
        inserted->prev = (*head)->prev;
        (*head)->prev = inserted;
        inserted->next = (*head);
        (*head) = inserted;
    }
    return;
}

void delete(DOUBLYLINKEDLIST **head, DOUBLYLINKEDLIST **tail, int x){
    
    DOUBLYLINKEDLIST * canbedeleted = *head;
    
    if(*head == NULL && *tail == NULL){
        return;
    }
    
    if((*head) == (*tail) && (*head)->value == x){
        free((*head));
        *head = NULL;
        *tail = NULL;
        return;
    }
    
    while(canbedeleted != NULL){
        if(canbedeleted->value == x){
            
            if(canbedeleted == (*head))
            {
                *head = canbedeleted->next;
                (*head)->prev = NULL;
            }
            else if(canbedeleted == (*tail))
            {
                *tail = canbedeleted->prev;
                (*tail)->next = NULL;
            }
            else
            {
                canbedeleted->prev->next = canbedeleted->next;
                canbedeleted->next->prev = canbedeleted->prev;
            }
            
            free(canbedeleted);
            break;
        }else{
            canbedeleted = canbedeleted->next;
        }
    }
    return;
}

void deleteFirst(DOUBLYLINKEDLIST **head, DOUBLYLINKEDLIST **tail){
    
    DOUBLYLINKEDLIST * deleted = (*head);
    
    if(*head == NULL && *tail == NULL){
        return;
    }
    
    if((*head) == (*tail)){
        *head = NULL;
        *tail = NULL;
        free(deleted);
        return;
    }
    
    (*head) = (*head)->next;
    (*head)->prev = NULL;
    free(deleted);
    
    return;
}

void deleteLast(DOUBLYLINKEDLIST **head, DOUBLYLINKEDLIST **tail){
    
    DOUBLYLINKEDLIST * deleted = (*tail);
    
    if(*head == NULL && *tail == NULL){
        return;
    }
    
    if((*head) == (*tail)){
        *head = NULL;
        *tail = NULL;
        free(deleted);
        return;
    }
    
    (*tail) = (*tail)->prev;
    (*tail)->next = NULL;
    free(deleted);
    return;
}
