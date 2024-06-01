#pragma once
#include <string.h>
#include <stdio.h>
#include <float.h>

int const N = 20;

struct PersonalComputer
{
    float displaySize, ram;
    char cpu[N], os[N];
};

//A.2
void Init(PersonalComputer* pc, float displaySize, float ram, const char* cpu, const char* os);
//A.3
void Print(PersonalComputer* pc);
//A.4
bool Equals(PersonalComputer* pc1, PersonalComputer* pc2);
//A.5
bool Less(PersonalComputer* pc1, PersonalComputer* pc2);