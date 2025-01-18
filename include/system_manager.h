#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "types.h"

SystemState* initializeSystem(void);
void cleanupSystem(SystemState* state);
bool saveSystemState(const SystemState* state, const char* filename);
SystemState* loadSystemState(const char* filename);
void* safeAlloc(size_t size);

#endif
