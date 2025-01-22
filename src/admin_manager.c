#include "../include/admin_manager.h"

Admin* adminHead = NULL;

bool validateAdmin(const char* username, const char* password) {
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        printf("Invalid input.\n");
        return false;
    }

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
    if (strcmp(username, "") == 0 || strcmp(newPassword, "") == 0) {
        printf("Invalid input.\n");
        return;
    }

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

void saveAdminCredentials(void) {
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

void loadAdminCredentials(void) {
    FILE* file = fopen("resources/db/admin_credentials.dat", "rb");
    if (!file) {

        Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
        if (newAdmin) {
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

bool adminExists(const char* username) {
    if (strcmp(username, "") == 0) {
        printf("Invalid input.\n");
        return false;
    }

    Admin* temp = adminHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void addAdmin(const char* username, const char* password) {
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        printf("Invalid input.\n");
        return;
    }

    if (adminExists(username)) {
        printf("Admin with username '%s' already exists.\n", username);
        return;
    }

    Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
    if (!newAdmin) {
        printf("Memory allocation failed!\n");
        return;
    }
    strncpy(newAdmin->username, username, sizeof(newAdmin->username) - 1);
    newAdmin->username[sizeof(newAdmin->username) - 1] = '\0';
    strncpy(newAdmin->password, password, sizeof(newAdmin->password) - 1);
    newAdmin->password[sizeof(newAdmin->password) - 1] = '\0';
    newAdmin->next = adminHead;
    adminHead = newAdmin;

    saveAdminCredentials();
    printf("New admin added: %s\n", newAdmin->username);
}

void deleteAdmin(const char* username) {
    if (strcmp(username, "") == 0) {
        printf("Invalid input.\n");
        return;
    }

    Admin* temp = adminHead;
    Admin* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            if (prev == NULL) {

                adminHead = temp->next;
            } else {
                prev->next = temp->next;
            }
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
    printf("\nRegistered Admins:\n");
    while (temp != NULL) {
        printf("\tUsername: %s\n", temp->username);
        temp = temp->next;
        if (temp != NULL) {
            printf("\t----------------------------------\n");
        }
    }
}

void freeAdmin(void) {
    Admin* current = adminHead;
    while (current != NULL) {
        Admin* temp = current;
        current = current->next;
        free(temp);
    }
    adminHead = NULL;
}
