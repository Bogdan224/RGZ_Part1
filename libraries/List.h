#pragma once
#include "PersonalComputer.h"
#include <stdlib.h>
struct List
{
    PersonalComputer* pc;
    List* next;
};

//B.2
void Push_back(PersonalComputer* pc, List** head);
//B.3
int Size(List* head);
//B.4
int DeleteByPos(List** head, int pos);
//B.5
PersonalComputer* GetElementByPos(List* head, int pos);

