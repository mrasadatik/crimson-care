#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Admin {
    uint32_t id;
    char username[20];
    char password[20];
    struct Admin* next;
} Admin;

bool validateAdmin(const char* username, const char* password);
void changeAdminPassword(const char* username, const char* newPassword);
void saveAdminCredentials(void);
void loadAdminCredentials(void);
void addAdmin(const char* username, const char* password);
void deleteAdmin(const char* username);
void displayAdmin(void);

#endif 
