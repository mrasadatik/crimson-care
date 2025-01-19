#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    char bloodGroup[BLOOD_GROUP_NAME_LENGTH];
    float price;
    uint32_t quantity;
    while (fscanf(file, "%s %f %u", bloodGroup, &price, &quantity) != EOF) {

        updateBloodPrice(bloodGroup, price);
        updateBloodQuantity(bloodGroup, quantity);
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
        fprintf(file, "%s %.2f %u\n", temp->bloodGroup, temp->price, temp->quantity);
        temp = temp->next;
    }
    fclose(file);
}

void displayBloodGroups(void) {
    BloodStock* temp = bloodHead;
    int i = 1;

    printf("\nAvailable Blood Groups:\n");
    while (temp != NULL) {
        printf("%s\n", temp->bloodGroup);
        i++;
        temp = temp->next;
    }
    if (i == 1) {
        printf("No available blood groups.\n");
    }
}

void displayBloodStocks(void) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->price > 0.0) {
            printf("Blood Group: %s, Price: %.2f, Quantity: %u\n", temp->bloodGroup, temp->price, temp->quantity);
        } else {
            printf("Blood Group: %s, Price: Not Set, Quantity: %u\n", temp->bloodGroup, temp->quantity);
        }
        temp = temp->next;
    }
}

bool updateBloodQuantity(const char* bloodGroup, uint32_t newQuantity) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (strcmp(temp->bloodGroup, bloodGroup) == 0) {
            temp->quantity = newQuantity;
            saveBloodGroups();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool updateBloodPrice(const char* bloodGroup, float newPrice) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (strcmp(temp->bloodGroup, bloodGroup) == 0) {
            temp->price = newPrice;
            saveBloodGroups();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity) {
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

bool isBloodGroupAvailable(const char* bloodGroup) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (strcmp(temp->bloodGroup, bloodGroup) == 0 && temp->price > 0 && temp->quantity > 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isBloodAvailable(TransactionType type) {
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

bool isValidBloodGroup(const char* bloodGroup) {
    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (strcmp(temp->bloodGroup, bloodGroup) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}


