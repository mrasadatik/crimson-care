#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/hospital_manager.h"

Hospital* hospitalHead = NULL;

bool addHospital(const char* name, const char* location) {
    char code[20];
    char initials[4] = { 0 };
    int initialCount = 0;

    char nameCopy[50];
    strncpy(nameCopy, name, sizeof(nameCopy) - 1);
    nameCopy[sizeof(nameCopy) - 1] = '\0';

    char* token = strtok(nameCopy, " ");
    while (token != NULL && initialCount < 3) {
        initials[initialCount++] = token[0];
        token = strtok(NULL, " ");
    }
    initials[initialCount] = '\0';

    bool codeExists;
    int randomSuffix;
    do {
        srand(time(NULL));
        randomSuffix = rand() % 10000;
        snprintf(code, sizeof(code), "%s%d", initials, randomSuffix);

        codeExists = false;
        Hospital* temp = hospitalHead;
        while (temp != NULL) {
            if (strcmp(temp->code, code) == 0) {
                codeExists = true;
                break;
            }
            temp = temp->next;
        }
    } while (codeExists);

    Hospital* newHospital = (Hospital*)malloc(sizeof(Hospital));
    if (!newHospital) {
        printf("Memory allocation failed!\n");
        return false;
    }

    strncpy(newHospital->code, code, sizeof(newHospital->code) - 1);
    newHospital->code[sizeof(newHospital->code) - 1] = '\0';
    strncpy(newHospital->name, name, sizeof(newHospital->name) - 1);
    newHospital->name[sizeof(newHospital->name) - 1] = '\0';
    strncpy(newHospital->location, location, sizeof(newHospital->location) - 1);
    newHospital->location[sizeof(newHospital->location) - 1] = '\0';
    newHospital->next = NULL;

    if (hospitalHead == NULL) {
        hospitalHead = newHospital;
    } else {
        Hospital* temp = hospitalHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newHospital;
    }

    saveHospitals();
    printf("Hospital added: %s (Code: %s)\n", name, code);
    return true;
}

bool validateHospitalCode(const char* code) {
    Hospital* temp = hospitalHead;
    while (temp != NULL) {
        if (strcmp(temp->code, code) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void displayHospitals() {
    Hospital* temp = hospitalHead;
    printf("\nRegistered Hospitals:\n");
    while (temp != NULL) {
        printf("Code: %s, Name: %s, Location: %s\n", temp->code, temp->name, temp->location);
        temp = temp->next;
    }
}

void saveHospitals() {
    FILE* file = fopen("resources/db/hospitals.txt", "w");
    if (!file) {
        printf("Error saving hospitals!\n");
        return;
    }

    Hospital* temp = hospitalHead;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%s\n", temp->code, temp->name, temp->location);
        temp = temp->next;
    }
    fclose(file);
}

void loadHospitals() {
    FILE* file = fopen("resources/db/hospitals.txt", "r");
    if (!file) {

        file = fopen("resources/db/hospitals.txt", "w");
        if (!file) {
            printf("Error creating hospitals file!\n");
            return;
        }
        fclose(file);
        return;
    }

    char code[20];
    char name[50];
    char location[50];

    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", code, name, location) != EOF) {

        Hospital* newHospital = (Hospital*)malloc(sizeof(Hospital));
        if (!newHospital) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        strncpy(newHospital->code, code, sizeof(newHospital->code) - 1);
        newHospital->code[sizeof(newHospital->code) - 1] = '\0';
        strncpy(newHospital->name, name, sizeof(newHospital->name) - 1);
        newHospital->name[sizeof(newHospital->name) - 1] = '\0';
        strncpy(newHospital->location, location, sizeof(newHospital->location) - 1);
        newHospital->location[sizeof(newHospital->location) - 1] = '\0';
        newHospital->next = NULL;

        if (hospitalHead == NULL) {
            hospitalHead = newHospital;
        } else {
            Hospital* temp = hospitalHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newHospital;
        }
    }
    fclose(file);
}
