#include "../include/blood_manager.h"
#include "../include/transaction_manager.h"

BloodStock* bloodHead = NULL;

void initializeBloodGroups(void) {

    addBloodGroup(1, "A+", 0.0, 0);
    addBloodGroup(2, "A-", 0.0, 0);
    addBloodGroup(3, "B+", 0.0, 0);
    addBloodGroup(4, "B-", 0.0, 0);
    addBloodGroup(5, "O+", 0.0, 0);
    addBloodGroup(6, "O-", 0.0, 0);
    addBloodGroup(7, "AB+", 0.0, 0);
    addBloodGroup(8, "AB-", 0.0, 0);
}

void loadBloodGroups(void) {
    FILE* file = fopen("resources/db/blood_data.txt", "r");
    if (!file) {
        initializeBloodGroups();
        return;
    }

    while (1) {
        BloodStock* newBlood = (BloodStock*)malloc(sizeof(BloodStock));
        if (!newBlood) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        if (fscanf(file, "%u %s %f %u", &newBlood->id, newBlood->bloodGroup, &newBlood->price, &newBlood->quantity) != 4) {
            free(newBlood);
            break;
        }

        updateBloodPrice(newBlood->id, newBlood->price);
        updateBloodQuantity(newBlood->id, newBlood->quantity);

        newBlood->next = NULL;

        if (bloodHead == NULL) {
            bloodHead = newBlood;
        } else {
            BloodStock* temp = bloodHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBlood;
        }
    }

    fclose(file);
}

void saveBloodGroups(void) {
    FILE* file = fopen("resources/db/blood_data.txt", "w");
    if (!file) {
        printf("Error saving blood groups!\n");
        return;
    }

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        fprintf(file, "%u %s %.2f %u\n", temp->id, temp->bloodGroup, temp->price, temp->quantity);
        temp = temp->next;
    }
    fclose(file);
}

void displayBloodGroups(void) {
    BloodStock* temp = bloodHead;

    bool bloodAvailable = false;
    bool firstBlood = true;
    while (temp != NULL) {
        if (firstBlood) {
            printf("\nAvailable Blood:\n");
            firstBlood = false;
        }
        printf("%u. %s\n", temp->id, temp->bloodGroup);
        bloodAvailable = true;
        temp = temp->next;
    }
    if (!bloodAvailable) {
        printf("No available blood groups.\n");
    }
}

void displayBloodStocks(void) {
    BloodStock* temp = bloodHead;
    if (temp == NULL) {
        printf("No blood available.\n");
        return;
    }
    bool bloodAvailable = false;
    bool firstBlood = true;
    while (temp != NULL) {
        if (temp->price > 0.0) {
            if (firstBlood) {
                printf("\nAvailable Blood:\n");
                firstBlood = false;
            }
            printf("%u. %s, Price: %.2f, Quantity: %u\n", temp->id, temp->bloodGroup, temp->price, temp->quantity);
            bloodAvailable = true;
        }
        temp = temp->next;
    }
    if (!bloodAvailable) {
        printf("No blood available.\n");
    }
}

bool updateBloodQuantity(uint32_t id, uint32_t newQuantity) {

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->quantity = newQuantity;
            saveBloodGroups();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool updateBloodPrice(uint32_t id, float newPrice) {

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->price = newPrice;
            saveBloodGroups();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity) {
    if (strcmp(bloodGroup, "") == 0) {
        printf("Invalid input.\n");
        return;
    }

    BloodStock* newGroup = (BloodStock*)malloc(sizeof(BloodStock));
    if (!newGroup) {
        printf("Memory allocation failed!\n");
        return;
    }
    strncpy(newGroup->bloodGroup, bloodGroup, BLOOD_GROUP_NAME_LENGTH - 1);
    newGroup->bloodGroup[BLOOD_GROUP_NAME_LENGTH - 1] = '\0';
    newGroup->price = price;
    newGroup->quantity = quantity;
    newGroup->id = id;
    newGroup->next = NULL;

    if (bloodHead == NULL) {
        bloodHead = newGroup;
    } else {
        BloodStock* temp = bloodHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newGroup;
    }
}

bool isAnyBloodAvailable(TransactionType type) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (type == BUY) {
            if (temp->price > 0 && temp->quantity > 0) {
                return true;
            }
        } else {
            if (temp->price > 0) {
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}

bool isBloodAvailable(uint32_t id, TransactionType type) {

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (type == BUY) {
            if (temp->id == id && temp->price > 0 && temp->quantity > 0) {
                return true;
            }
        } else {
            if (temp->id == id && temp->price > 0) {
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}

bool isValidBloodGroup(uint32_t id) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

char* getBloodGroupById(uint32_t id) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp->bloodGroup;
        }
        temp = temp->next;
    }
    return NULL;
}

void freeBloodList(void) {
    BloodStock* current = bloodHead;
    while (current != NULL) {
        BloodStock* temp = current;
        current = current->next;
        free(temp);
    }
    bloodHead = NULL;
}

