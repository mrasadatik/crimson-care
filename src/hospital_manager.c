#include "../include/hospital_manager.h"

/*!
 * @brief Hospital head to track hospitals on runtime
 */
Hospital* hospitalHead = NULL;

/*!
 * @brief Load hospitals from file
 */
void loadHospitals(void) {
    errno = 0;
    FILE* file = fopen("resources/db/hospitals.txt", "r");
    if (!file) {
        if (errno == ENOENT) {
            return;
        } else {
            printf("Error opening hospitals file: %s\n", strerror(errno));
            freeHospital();
            return;
        }
    }

    while (1) {
        Hospital* newHospital = (Hospital*)malloc(sizeof(Hospital));
        if (!newHospital) {
            printf("Error allocating memory for hospital: %s\n", strerror(errno));
            fclose(file);
            freeHospital();
            return;
        }

        if (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", newHospital->code, newHospital->name, newHospital->location) != 3) {
            free(newHospital);
            fclose(file);
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

/*!
 * @brief Save hospitals to file
 */
void saveHospitals(void) {
    errno = 0;
    FILE* file = fopen("resources/db/hospitals.txt", "w");
    if (!file) {
        printf("Error opening hospitals file: %s\n", strerror(errno));
        return;
    }

    Hospital* temp = hospitalHead;
    while (temp != NULL) {
        fprintf(file, "%s|%s|%s\n", temp->code, temp->name, temp->location);
        temp = temp->next;
    }
    fclose(file);
}

/*!
 * @brief Add hospital
 *
 * @param[in] name Hospital name
 * @param[in] location Hospital location
 *
 * @return Hospital code or NULL if hospital is not added
 */
char* addHospital(const char* name, const char* location) {
    if (strcmp(name, "") == 0 || strcmp(location, "") == 0) {
        printf("Error: Hospital name or location cannot be empty.\n");
        return NULL;
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
        printf("Error allocating memory for hospital: %s\n", strerror(errno));
        return NULL;
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
    return newHospital->code;
}

/*!
 * @brief Validate hospital code
 *
 * @param[in] code Hospital code
 *
 * @return True if hospital code is valid, False otherwise
 */
bool validateHospitalCode(const char* code) {
    if (strcmp(code, "") == 0) {
        printf("Error: Hospital code cannot be empty.\n");
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

/*!
 * @brief Delete hospital
 *
 * @param[in] code Hospital code
 * @param[in] adminUsername Admin username
 * @param[in] adminPassword Admin password
 *
 * @return True if hospital is deleted, False otherwise
 */
bool deleteHospital(const char* code, const char* adminUsername, const char* adminPassword) {
    if (strcmp(adminUsername, "") == 0 || strcmp(adminPassword, "") == 0) {
        printf("Error: Admin credentials cannot be empty.\n");
        return false;
    }

    if (!validateAdmin(adminUsername, adminPassword)) {
        printf("Error: Invalid admin credentials.\n");
        return false;
    }

    if (strcmp(code, "") == 0) {
        printf("Error: Hospital code cannot be empty.\n");
        return false;
    }

    if (!validateHospitalCode(code)) {
        printf("Error: Hospital code is invalid.\n");
        return false;
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
            saveHospitals();
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

/*!
 * @brief Get hospital name by code
 *
 * @param[in] code Hospital code
 *
 * @return Hospital name or NULL if not found
 */
char* getHospitalNameByCode(const char* code) {
    if (strcmp(code, "") == 0) {
        printf("Error: Hospital code cannot be empty.\n");
        return NULL;
    }

    if (!validateHospitalCode(code)) {
        printf("Error: Hospital code is invalid.\n");
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

/*!
 * @brief Display all hospitals
 */
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

/*!
 * @brief Free hospital list from memory
 */
void freeHospital(void) {
    Hospital* current = hospitalHead;
    while (current != NULL) {
        Hospital* temp = current;
        current = current->next;
        free(temp);
    }
    hospitalHead = NULL;
}
