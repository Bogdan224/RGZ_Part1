#include "WashingMachine.h"
void Init(WashingMachine* wm, float price, float mss, const char* model, const char* firm) {
    if (price < 0 || price > FLT_MAX)
        price = 0;
    wm->price = price;
    if (mss < 0 || mss > FLT_MAX)
        mss = 0;
    wm->mss = mss;
    if (strlen(model) > N)
        model = "Undefined";
    strncpy(wm->model, model, N);
    if (strlen(firm) > N)
        firm = "Undefined";
    strncpy(wm->firm, firm, N);
}

//A.3
void Print(WashingMachine* wm) {
   printf("Price: %f\nMotor spin speed: %f\nModel: %s\nFirm: %s\n", wm->price, wm->mss, wm->model, wm->firm);
}
//A.4
bool Equals(WashingMachine* wm1, WashingMachine* wm2){
    if (wm1->price != wm2->price)
        return false;
    if (wm1->mss != wm2->mss)
        return false;
    if (strcmp(wm1->model, wm2->model) != 0)
        return false;
    if (strcmp(wm1->firm, wm2->firm) != 0)
        return false;
    return true;
}
//A.5
bool Less(WashingMachine* wm1, WashingMachine* wm2){
    if (wm1->price >= wm2->price)
        return false;
    if (wm1->mss >= wm2->mss)
        return false;
    if (strcmp(wm1->model, wm2->model) != -1)
        return false;
    if (strcmp(wm1->firm, wm2->firm) != -1)
        return false;
    return true;
}