#include "../include/hospital_manager.h"

Hospital* hospitalHead = NULL;

bool addHospital(const char* name, const char* location) {
    if (strcmp(name, "") == 0 || strcmp(location, "") == 0) {
        printf("Invalid input.\n");
        return false;
    }
    char code[8];
    char initials[4] = { 0 };
    int initialCount = 0;

    char nameCopy[100];
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
    if (strcmp(code, "") == 0) {
        printf("Invalid input.\n");
        return false;
    }

    Hospital* temp = hospitalHead;
    while (temp != NULL) {
        if (strcmp(temp->code, code) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void displayHospitals(void) {
    Hospital* temp = hospitalHead;
    if (temp == NULL) {
        printf("No hospitals registered yet.\n");
        return;
    }
    printf("\nRegistered Hospitals:\n");
    while (temp != NULL) {
        printf("\tCode: %s\n"
            "\tName: %s\n"
            "\tLocation: %s\n", temp->code, temp->name, temp->location);
        temp = temp->next;
        if (temp != NULL) {
            printf("\t----------------------------------\n");
        }
    }
}

void saveHospitals(void) {
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

void loadHospitals(void) {
    FILE* file = fopen("resources/db/hospitals.txt", "r");
    if (!file) {
        printf("Error opening hospitals file!\n");
        return;
    }

    while (1) {
        Hospital* newHospital = (Hospital*)malloc(sizeof(Hospital));
        if (!newHospital) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        if (fscanf(file, "%[^,],%[^,],%[^\n]\n", newHospital->code, newHospital->name, newHospital->location) != 3) {
            free(newHospital);
            break;
        }

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

char* getHospitalNameByCode(const char* code) {
    if (strcmp(code, "") == 0) {
        printf("Invalid input.\n");
        return NULL;
    }

    Hospital* temp = hospitalHead;
    while (temp != NULL) {
        if (strcmp(temp->code, code) == 0) {
            return temp->name;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteHospital(const char* code) {
    if (strcmp(code, "") == 0) {
        printf("Invalid input.\n");
        return;
    }

    Hospital* current = hospitalHead;
    Hospital* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->code, code) == 0) {
            if (prev == NULL) {
                hospitalHead = current->next;
            } else {
                prev->next = current->next;
            }
            printf("Hospital deleted successfully.\n");
            saveHospitals();
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Hospital with code '%s' not found.\n", code);
}

void freeHospital(void) {
    Hospital* current = hospitalHead;
    while (current != NULL) {
        Hospital* temp = current;
        current = current->next;
        free(temp);
    }
    hospitalHead = NULL;
}
