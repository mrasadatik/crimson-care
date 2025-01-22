#ifndef HOSPITAL_MANAGER_H
#define HOSPITAL_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


typedef struct Hospital {
    char code[8];
    char name[100];
    char location[100];
    struct Hospital* next;
} Hospital;


bool addHospital(const char* name, const char* location);
bool validateHospitalCode(const char* code);
void loadHospitals(void);
void displayHospitals(void);
void deleteHospital(const char* code);
void saveHospitals(void);
void freeHospital(void);
char* getHospitalNameByCode(const char* code);

#endif
