#include "../include/admin_manager.h"

/*!
 * @brief Admin head to track admins on runtime
 */
Admin* adminHead = NULL;

/*!
 * @brief Save admin credentials to file
 */
void saveAdminCredentials(void) {
    errno = 0;
    FILE* file = fopen("resources/db/admin_credentials.dat", "wb");
    if (!file) {
        if (errno != ENOENT) {
            printf("Error opening admin credentials file: %s\n", strerror(errno));
            return;
        }
    }

    Admin* temp = adminHead;
    while (temp != NULL) {
        fwrite(temp, sizeof(Admin), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

/*!
 * @brief Load admin credentials from file
 */
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
                printf("Error allocating memory for admin: %s\n", strerror(errno));
            }
        } else {
            printf("Error opening admin credentials file: %s\n", strerror(errno));
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
            printf("Error allocating memory for admin: %s\n", strerror(errno));
            freeAdmin();
            fclose(file);
            return;
        }
    }
    fclose(file);
}

/*!
 * @brief Check if admin exists
 *
 * @param[in] username Admin username
 *
 * @return True if admin exists, False otherwise
 */
bool adminExists(const char* username) {
    if (strcmp(username, "") == 0) {
        printf("Error: Admin username cannot be empty.\n");
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

/*!
 * @brief Validate admin credentials
 *
 * @param[in] username Admin username
 * @param[in] password Admin password
 *
 * @return True if credentials are valid, False otherwise
 */
bool validateAdmin(const char* username, const char* password) {
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        printf("Error: Admin credentials cannot be empty.\n");
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

/*!
 * @brief Add admin
 *
 * @param[in] username Admin username
 * @param[in] password Admin password
 * @param[in] currentAdminUsername Current admin username
 * @param[in] currentAdminPassword Current admin password
 *
 * @return True if admin is added, False otherwise
 */
bool addAdmin(const char* username, const char* password, const char* currentAdminUsername, const char* currentAdminPassword) {
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        printf("Error: Admin credentials cannot be empty.\n");
        return false;
    }

    if (!validateAdmin(currentAdminUsername, currentAdminPassword)) {
        printf("Error: Invalid current admin credentials.\n");
        return false;
    }

    if (adminExists(username)) {
        printf("Error: Admin already exists.\n");
        return false;
    }

    Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
    if (!newAdmin) {
        printf("Error allocating memory for admin: %s\n", strerror(errno));
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

/*!
 * @brief Delete admin
 *
 * @param[in] username Admin username
 * @param[in] currentAdminUsername Current admin username
 * @param[in] currentAdminPassword Current admin password
 *
 * @return True if admin is deleted, False otherwise
 */
bool deleteAdmin(const char* username, const char* currentAdminUsername, const char* currentAdminPassword) {
    if (strcmp(username, "") == 0) {
        printf("Error: Admin username cannot be empty.\n");
        return false;
    }

    if (!validateAdmin(currentAdminUsername, currentAdminPassword)) {
        printf("Error: Invalid current admin credentials.\n");
        return false;
    }

    if (!adminExists(username)) {
        printf("Error: Admin does not exist.\n");
        return false;
    }

    if (strcmp(username, currentAdminUsername) == 0) {
        printf("Error: Cannot delete current admin.\n");
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
            free(temp);
            saveAdminCredentials();
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

/*!
 * @brief Change admin password
 *
 * @param[in] username Admin username
 * @param[in] oldPassword Old password
 * @param[in] newPassword New password
 *
 * @return True if password is changed, False otherwise
 */
bool changeAdminPassword(const char* username, const char* oldPassword, const char* newPassword) {
    if (strcmp(username, "") == 0 || strcmp(oldPassword, "") == 0) {
        printf("Error: Username or old password cannot be empty.\n");
        return false;
    }

    if (!validateAdmin(username, oldPassword)) {
        printf("Error: Invalid password.\n");
        return false;
    }

    if (strcmp(newPassword, "") == 0) {
        printf("Error: New password cannot be empty.\n");
        return false;
    }

    Admin* temp = adminHead;
    while (temp != NULL) {
        if (strcmp(username, temp->username) == 0 && strcmp(oldPassword, temp->password) == 0) {
            strncpy(temp->password, newPassword, sizeof(temp->password) - 1);
            temp->password[sizeof(temp->password) - 1] = '\0';
            saveAdminCredentials();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/*!
 * @brief Display all admins
 */
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

/*!
 * @brief Free admin list
 */
void freeAdmin(void) {
    Admin* current = adminHead;
    while (current != NULL) {
        Admin* temp = current;
        current = current->next;
        free(temp);
    }
    adminHead = NULL;
}
