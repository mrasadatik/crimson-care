#include "../include/admin_manager.h"

Admin* adminHead = NULL;

bool validateAdmin(const char* username, const char* password) {
    errno = 0;
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        errno = EINVAL;
        perror("Error");
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

bool changeAdminPassword(const char* username, const char* newPassword) {
    errno = 0;
    if (strcmp(username, "") == 0 || strcmp(newPassword, "") == 0) {
        errno = EINVAL;
        perror("Error");
        return false;
    }

    Admin* temp = adminHead;
    while (temp != NULL) {
        if (strcmp(username, temp->username) == 0) {
            strncpy(temp->password, newPassword, sizeof(temp->password) - 1);
            temp->password[sizeof(temp->password) - 1] = '\0';
            printf("Password changed successfully!\n");
            saveAdminCredentials();
            return true;
        }
        temp = temp->next;
    }
    printf("Invalid username. Password change failed.\n");
    return false;
}

void saveAdminCredentials(void) {
    errno = 0;
    FILE* file = fopen("resources/db/admin_credentials.dat", "wb");
    if (!file) {
        perror("Error");
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
    errno = 0;
    FILE* file = fopen("resources/db/admin_credentials.dat", "rb");
    if (!file) {
        if (errno == ENOENT) {
            Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
            if (newAdmin) {
                strcpy(newAdmin->username, "admin");
                strcpy(newAdmin->password, "1234");
                newAdmin->next = NULL;
                adminHead = newAdmin;
                saveAdminCredentials();
            } else {
                perror("Error");
            }
        } else {
            perror("Error");
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
        } else {
            perror("Error");
        }
    }
    fclose(file);
}

bool adminExists(const char* username) {
    errno = 0;
    if (strcmp(username, "") == 0) {
        errno = EINVAL;
        perror("Error");
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

bool addAdmin(const char* username, const char* password) {
    errno = 0;
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        errno = EINVAL;
        perror("Error");
        return false;
    }

    if (adminExists(username)) {
        errno = EEXIST;
        perror("Error");
        return false;
    }

    Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
    if (!newAdmin) {
        perror("Error");
        return false;
    }
    strncpy(newAdmin->username, username, sizeof(newAdmin->username) - 1);
    newAdmin->username[sizeof(newAdmin->username) - 1] = '\0';
    strncpy(newAdmin->password, password, sizeof(newAdmin->password) - 1);
    newAdmin->password[sizeof(newAdmin->password) - 1] = '\0';
    newAdmin->next = adminHead;
    adminHead = newAdmin;

    saveAdminCredentials();
    return true;
}

bool deleteAdmin(const char* username) {
    errno = 0;
    if (strcmp(username, "") == 0) {
        errno = EINVAL;
        perror("Error");
        return false;
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
            saveAdminCredentials();
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    errno = ENODATA;
    perror("Error");
    return false;
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
