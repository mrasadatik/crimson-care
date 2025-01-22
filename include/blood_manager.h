#ifndef BLOOD_MANAGER_H
#define BLOOD_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "transaction_manager.h"

#define BLOOD_GROUP_NAME_LENGTH 4

typedef struct BloodStock {
    float price;
    uint32_t id;
    uint32_t quantity;
    char bloodGroup[BLOOD_GROUP_NAME_LENGTH];
    struct BloodStock* next;
} BloodStock;

extern BloodStock* bloodHead;

void initializeBloodGroups(void);
void loadBloodGroups(void);
void saveBloodGroups(void);
void addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity);
void displayBloodGroups(void);
bool updateBloodQuantity(uint32_t id, uint32_t newQuantity);
bool updateBloodPrice(uint32_t id, float newPrice);
bool isValidBloodGroup(uint32_t id);
bool isAnyBloodAvailable(TransactionType type);
bool isBloodAvailable(uint32_t id, TransactionType type);
void displayBloodStocks(void);
char* getBloodGroupById(uint32_t id);
void freeBloodList(void);

#endif
