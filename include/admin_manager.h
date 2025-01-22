#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Admin {
    char username[20];
    char password[20];
    struct Admin* next;
} Admin;

bool validateAdmin(const char* username, const char* password);
bool changeAdminPassword(const char* username, const char* newPassword);
void saveAdminCredentials(void);
void loadAdminCredentials(void);
bool addAdmin(const char* username, const char* password);
bool deleteAdmin(const char* username);
void displayAdmin(void);
void freeAdmin(void);

#endif
