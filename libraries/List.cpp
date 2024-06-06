#include "List.h"
void Push_back(WashingMachine* wm, List** head) {
    if (*head == NULL) {
        *head = (List*)malloc(sizeof(List));
        (*head)->wm = wm;
        (*head)->next = NULL;
        return;
    }
    Push_back(wm, &(*head)->next);
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
        free((*head)->wm);
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
    free(tmp->wm);
    free(tmp);
    return 0;
}
//B.5
WashingMachine* GetElementByPos(List* head, int pos) {
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
    return head->wm;
}

