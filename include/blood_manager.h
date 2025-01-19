#ifndef BLOOD_MANAGER_H
#define BLOOD_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

#include "transaction_manager.h"

#define BLOOD_GROUP_NAME_LENGTH 4

typedef struct BloodStock {
    uint32_t id;
    char bloodGroup[BLOOD_GROUP_NAME_LENGTH];
    float price;
    uint32_t quantity;
    struct BloodStock* next;
} BloodStock;

extern BloodStock* bloodHead;

void initializeBloodGroups(void);
void loadBloodGroups(void);
void saveBloodGroups(void);
void addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity);
void displayBloodGroups(void);
bool updateBloodQuantity(const char* bloodGroup, uint32_t newQuantity);
bool updateBloodPrice(const char* bloodGroup, float newPrice);
bool isBloodGroupAvailable(const char* bloodGroup);
bool isValidBloodGroup(const char* bloodGroup);
bool isBloodAvailable(TransactionType type);
void displayBloodStocks(void);

#endif 
