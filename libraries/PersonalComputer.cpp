#include "PersonalComputer.h"
void Init(PersonalComputer* pc, float displaySize, float ram, const char* cpu, const char* os) {
    if (displaySize < 0 || displaySize > FLT_MAX)
        displaySize = 0;
    pc->displaySize = displaySize;
    if (ram < 0 || ram > FLT_MAX)
        ram = 0;
    pc->ram = ram;
    if (strlen(cpu) > N)
        cpu = "Undefined";
    strncpy(pc->cpu, cpu, N);
    if (strlen(os) > N)
        os = "Undefined";
    strncpy(pc->os, os, N);
}

//A.3
void Print(PersonalComputer* pc) {
   printf("Display size: %f\nRAM: %f\nCPU: %s\nOS: %s\n", pc->displaySize, pc->ram, pc->cpu, pc->os);
}
//A.4
bool Equals(PersonalComputer* pc1, PersonalComputer* pc2){
    if (pc1->displaySize != pc2->displaySize)
        return false;
    if (pc1->ram != pc2->ram)
        return false;
    if (strcmp(pc1->cpu, pc2->cpu) != 0)
        return false;
    if (strcmp(pc1->os, pc2->os) != 0)
        return false;
    return true;
}
//A.5
bool Less(PersonalComputer* pc1, PersonalComputer* pc2){
    if (pc1->displaySize >= pc2->displaySize)
        return false;
    if (pc1->ram >= pc2->ram)
        return false;
    if (strcmp(pc1->cpu, pc2->cpu) != -1)
        return false;
    if (strcmp(pc1->os, pc2->os) != -1)
        return false;
    return true;
}