#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include "types.h"

bool addAdmin(SystemState* state, const char* id, const char* password, bool is_super);
Admin* findAdmin(SystemState* state, const char* id);
bool removeAdmin(SystemState* state, const char* id);
bool changeAdminPassword(SystemState* state, const char* adminId,
                        const char* oldPassword, const char* newPassword);
bool validateAdmin(SystemState* state, const char* id, const char* password);

#endif
