#include "List.h"
void Push_back(PersonalComputer* pc, List** head) {
    if (*head == NULL) {
        *head = (List*)malloc(sizeof(List));
        (*head)->pc = pc;
        (*head)->next = NULL;
        return;
    }
    Push_back(pc, &(*head)->next);
}

//B.3
int Size(List* head) {
    int size = 0;
    while (head != NULL) {
        head = head->next;
        ++size;
    }
    return size;
}
//B.4
int DeleteByPos(List** head, int pos) {
    if(*head == NULL)
        return 2;
    if (pos < 0) 
        return 1;
    if (pos == 0) {
        List* next = (*head)->next;
        free((*head)->pc);
        free((*head));
        *head = next;
        return 0;
    }
    List* res = (*head);
    List* pred = (*head);
    List* tmp = (*head);
    for (size_t i = 0; i < pos; i++)
    {
        if (tmp == NULL) {
            return 1;
        }
        pred = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return 1;
    }
    pred->next = tmp->next;
    free(tmp->pc);
    free(tmp);
    return 0;
}
//B.5
PersonalComputer* GetElementByPos(List* head, int pos) {
    if (pos < 0) {
        return NULL;
    }
    List* res = head;
    for (size_t i = 0; i < pos; i++)
    {
        if (head == NULL) {
            printf("Error: there is no such this position!\n");
            return NULL;
        }
        head = head->next;
    }
    return head->pc;
}

