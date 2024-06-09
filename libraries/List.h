#pragma once
#include "WashingMachine.h"
#include <stdlib.h>
struct List
{
    WashingMachine* wm;
    List* next;
};

//B.2
void Push_back(WashingMachine* wm, List** head);
List* Push_front(WashingMachine* wm, List* head);
List* Push(WashingMachine* wm, List* head);
//B.3
int Size(List* head);
//B.4
int DeleteByPos(List** head, int pos);
//B.5
WashingMachine* GetElementByPos(List* head, int pos);

