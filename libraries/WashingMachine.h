#pragma once
#include <string.h>
#include <stdio.h>
#include <float.h>

int const N = 20;

struct WashingMachine
{
    float price, mss;
    char model[N], firm[N];
};

//A.2
void Init(WashingMachine* wm, float price, float mss, const char* model, const char* firm);
//A.3
void Print(WashingMachine* wm);
//A.4
bool Equals(WashingMachine* wm1, WashingMachine* wm2);
//A.5
bool Less(WashingMachine* wm1, WashingMachine* wm2);