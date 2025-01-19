#ifndef HOSPITAL_MANAGER_H
#define HOSPITAL_MANAGER_H

#include <stdbool.h>


typedef struct Hospital {
    char code[20];
    char name[50];
    char location[50];
    struct Hospital* next;
} Hospital;


bool addHospital(const char* name, const char* location);
bool validateHospitalCode(const char* code);
void loadHospitals();
void displayHospitals();
void saveHospitals();

#endif 
