#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/admin_manager.h"

Admin* adminHead = NULL;
static uint32_t nextAdminId = 1;

bool validateAdmin(const char* username, const char* password) {
    Admin* temp = adminHead;
    while (temp != NULL) {
        if (strcmp(username, temp->username) == 0 && strcmp(password, temp->password) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void changeAdminPassword(const char* username, const char* newPassword) {
    Admin* temp = adminHead;
    while (temp != NULL) {
        if (strcmp(username, temp->username) == 0) {
            strncpy(temp->password, newPassword, sizeof(temp->password) - 1);
            temp->password[sizeof(temp->password) - 1] = '\0';
            printf("Password changed successfully!\n");
            saveAdminCredentials();
            return;
        }
        temp = temp->next;
    }
    printf("Invalid username. Password change failed.\n");
}

void saveAdminCredentials() {
    FILE* file = fopen("resources/db/admin_credentials.dat", "wb");
    if (!file) {
        printf("Error saving admin credentials!\n");
        return;
    }

    Admin* temp = adminHead;
    while (temp != NULL) {
        fwrite(temp, sizeof(Admin), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

void loadAdminCredentials() {
    FILE* file = fopen("resources/db/admin_credentials.dat", "rb");
    if (!file) {

        Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
        if (newAdmin) {
            newAdmin->id = nextAdminId++;
            strcpy(newAdmin->username, "admin");
            strcpy(newAdmin->password, "1234");
            newAdmin->next = NULL;

            adminHead = newAdmin;
            saveAdminCredentials();
        }
        return;
    }

    Admin tempAdmin;
    while (fread(&tempAdmin, sizeof(Admin), 1, file)) {
        Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
        if (newAdmin) {
            *newAdmin = tempAdmin;
            newAdmin->next = adminHead;
            adminHead = newAdmin;
        }
    }
    fclose(file);
}

bool adminExists(const char* username, uint32_t id) {
    Admin* temp = adminHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 || temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void addAdmin(const char* username, const char* password) {

    if (adminExists(username, nextAdminId)) {
        printf("Admin with username '%s' or ID '%u' already exists.\n", username, nextAdminId);
        return;
    }

    Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
    if (!newAdmin) {
        printf("Memory allocation failed!\n");
        return;
    }
    newAdmin->id = nextAdminId++;
    strncpy(newAdmin->username, username, sizeof(newAdmin->username) - 1);
    newAdmin->username[sizeof(newAdmin->username) - 1] = '\0';
    strncpy(newAdmin->password, password, sizeof(newAdmin->password) - 1);
    newAdmin->password[sizeof(newAdmin->password) - 1] = '\0';
    newAdmin->next = adminHead;
    adminHead = newAdmin;

    saveAdminCredentials();
    printf("New admin added: %s (ID: %u)\n", newAdmin->username, newAdmin->id);
}

void deleteAdmin(const char* username) {
    Admin* temp = adminHead;
    Admin* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            if (prev == NULL) {

                adminHead = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Admin account deleted successfully.\n");
            saveAdminCredentials();
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Admin with username '%s' not found.\n", username);
}

void displayAdmin(void) {
    Admin* temp = adminHead;
    while (temp != NULL) {
        printf("Admin ID: %u, Username: %s\n", temp->id, temp->username);
        temp = temp->next;
    }
}