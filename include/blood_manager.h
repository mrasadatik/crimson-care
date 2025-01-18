#ifndef BLOOD_MANAGER_H
#define BLOOD_MANAGER_H

#include "types.h"

bool addBloodGroup(SystemState* state, const char* name, float price, uint16_t quantity);
bool removeBloodGroup(SystemState* state, const char* name);
BloodGroup* findBloodGroup(SystemState* state, const char* name);
bool updateBloodQuantity(SystemState* state, const char* name, uint16_t quantity);
bool updateBloodPrice(SystemState* state, const char* name, float price);
void displayBloodGroups(const SystemState* state);

#endif
