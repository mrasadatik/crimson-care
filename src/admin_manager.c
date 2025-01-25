/*!
 * @file admin_manager.c
 * @brief Admin manager source file
 * @details This file contains the implementation of the admin manager module.
 *
 * @author CrimsonCare Team
 * @date 2025-01-18
 *
 * @copyright
 * Copyright (c) 2025 CrimsonCare Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "../include/admin_manager.h"

 /*!
 * @brief Admin head pointer
 * @details This pointer is used to track admin linkedlist on runtime.
 */
Admin* adminHead = NULL;

/*!
 * @name saveAdminCredentials
 * @brief Save admin credentials to file
 * @details This function saves the linkedlist data
 * from `adminHead` to the file `resources/db/admin_credentials.dat`.
 * `.dat` is used to store credentials in binary format for surface level security.
 *
 * @note The file path 'resources/db' is relative to the project root directory.
 * Make sure that the folder exists also to run the program from the root directory.
 *
 * @post The linkedlist data is saved to the file.
 *
 * @exception fopen() - If the file cannot be opened, an error message is displayed.
 * @exception fwrite() - If the file cannot be written, an error message is displayed.
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
        if (fwrite(temp, sizeof(Admin), 1, file)) {
            temp = temp->next;
        } else {
            printf("Error writing admin credentials: %s\n", strerror(errno));
            freeAdmin();
            fclose(file);
            return;
        }
    }
    fclose(file);
}

/*!
 * @name loadAdminCredentials
 * @brief Load admin credentials from file
 * @details This function loads the admin credentials
 * from the file `resources/db/admin_credentials.dat` and
 * stores it in the `adminHead` linkedlist. If file is not found,
 * it creates a new admin with default credentials and stores it in the file.
 *
 * @note The file path 'resources/db' is relative to the project root directory.
 * Make sure that the folder exists also to run the program from the root directory.
 *
 * @post If the file is not found, a new admin is created with default credentials
 * and stored in the file. If the file is found, the admin credentials are loaded
 * from the file and stored in the `adminHead` linkedlist.
 *
 * @exception fopen() - If the file cannot be opened, an error message is displayed.
 * @exception malloc() - If memory allocation fails, an error message is displayed.
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
 * @name adminExists
 * @brief Check if admin exists
 * @details This function traverses the `adminHead` linkedlist
 * and checks if the username exists in the list.
 *
 * @param[in] username Admin username
 *
 * @return True if admin exists, False otherwise
 *
 * @pre @p username is not empty and valid
 * @post If the @p username is found in the linkedlist,
 * the function returns true, otherwise false.
 *
 * @exception If the @p username is empty, an error message is displayed.
 * @exception If the @p username is invalid, an error message is displayed.
 */
bool adminExists(const char* username) {
    if (strcmp(username, "") == 0) {
        printf("Error: Admin username cannot be empty.\n");
        return false;
    }

    if (!checkUsername(username)) {
        printf("Error: Invalid username. Username can only contain lowercase letters and digits.\n");
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
 * @name validateAdmin
 * @brief Validate admin credentials
 * @details This function traverses the `adminHead` linkedlist
 * and checks if the pair of username and password match.
 *
 * @param[in] username Admin username
 * @param[in] password Admin password
 *
 * @return True if credentials are valid, False otherwise
 *
 * @pre @p username and @p password are not empty and valid
 * @post If the pair of @p username and @p password are found in the linkedlist,
 * the function returns true, otherwise false.
 *
 * @exception If the @p username or @p password is empty, an error message is displayed.
 * @exception If the @p username is invalid, an error message is displayed.
 */
bool validateAdmin(const char* username, const char* password) {
    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        printf("Error: Admin credentials cannot be empty.\n");
        return false;
    }

    if (!checkUsername(username)) {
        printf("Error: Invalid username. Username can only contain lowercase letters and digits.\n");
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
 * @name addAdmin
 * @brief Add admin
 * @details This function adds a new admin to the `adminHead` linkedlist
 * and saves the updated linkedlist to the file `resources/db/admin_credentials.dat`.
 *
 * @param[in] username Admin username
 * @param[in] password Admin password
 * @param[in] currentAdminUsername Current admin username
 * @param[in] currentAdminPassword Current admin password
 *
 * @return True if admin is added, False otherwise
 *
 * @note The file path 'resources/db' is relative to the project root directory.
 * Make sure that the folder exists also to run the program from the root directory.
 *
 * @pre @p username and @p password are not empty
 * @pre @p currentAdminUsername and @p currentAdminPassword are not empty
 * @pre @p username and @p currentAdminUsername are valid
 * @post If the @p username and @p password are not found in the linkedlist,
 * the function adds the new admin to the linkedlist and saves the updated linkedlist to the file.
 *
 * @exception If the @p username or @p password is empty, an error message is displayed.
 * @exception If the @p username or @p currentAdminUsername is invalid, an error message is displayed.
 * @exception If the pair of @p currentAdminUsername and @p currentAdminPassword is invalid,
 * means that the current admin credentials are not valid, an error message is displayed.
 * @exception If the @p username already exists, an error message is displayed.
 * @exception malloc() - If memory allocation fails, an error message is displayed.
 */
bool addAdmin(const char* username, const char* password, const char* currentAdminUsername, const char* currentAdminPassword) {
    if (strcmp(currentAdminUsername, "") == 0 || strcmp(currentAdminPassword, "") == 0) {
        printf("Error: Current admin credentials cannot be empty.\n");
        return false;
    }

    if (!checkUsername(currentAdminUsername) || !checkUsername(username)) {
        printf("Error: Invalid username. Username can only contain lowercase letters and digits.\n");
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

    if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
        printf("Error: Admin credentials cannot be empty.\n");
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
 * @name deleteAdmin
 * @brief Delete admin
 * @details This function deletes an admin from the `adminHead` linkedlist
 * and saves the updated linkedlist.
 *
 * @param[in] username Admin username
 * @param[in] currentAdminUsername Current admin username
 * @param[in] currentAdminPassword Current admin password
 *
 * @return True if admin is deleted, False otherwise
 *
 * @pre @p username is not empty
 * @pre @p currentAdminUsername and @p currentAdminPassword are not empty
 * @pre @p username and @p currentAdminUsername are valid
 * @post If the @p username is found in the linkedlist,
 * the function deletes the admin from the linkedlist and saves the updated linkedlist to the file.
 *
 * @exception If the pair of @p currentAdminUsername and @p currentAdminPassword is invalid,
 * means that the current admin credentials are not valid, an error message is displayed.
 * @exception If the @p username does not exist, an error message is displayed.
 * @exception If the @p username is the same as the current admin username, an error message is displayed.
 * @exception If the @p username or @p currentAdminUsername is invalid, an error message is displayed.
 */
bool deleteAdmin(const char* username, const char* currentAdminUsername, const char* currentAdminPassword) {
    if (strcmp(currentAdminUsername, "") == 0 || strcmp(currentAdminPassword, "") == 0) {
        printf("Error: Current admin credentials cannot be empty.\n");
        return false;
    }

    if (!checkUsername(currentAdminUsername) || !checkUsername(username)) {
        printf("Error: Invalid username. Username can only contain lowercase letters and digits.\n");
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

    if (strcmp(username, "") == 0) {
        printf("Error: Admin username cannot be empty.\n");
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
 * @name changeAdminPassword
 * @brief Change admin password
 * @details This function changes the password of an admin in the `adminHead` linkedlist
 * and saves the updated linkedlist.
 *
 * @param[in] username Admin username
 * @param[in] oldPassword Old password
 * @param[in] newPassword New password
 *
 * @return True if password is changed, False otherwise
 *
 * @pre @p username and @p oldPassword are not empty
 * @pre @p username is valid
 * @pre @p newPassword is not empty
 * @post If the pair of @p username and @p oldPassword are found in the linkedlist,
 * the function changes the password of the admin and saves the updated linkedlist.
 *
 * @exception If the @p username or @p oldPassword is empty, an error message is displayed.
 * @exception If the pair of @p username and @p oldPassword is not found in the linkedlist,
 * an error message is displayed.
 * @exception If the @p username is invalid, an error message is displayed.
 */
bool changeAdminPassword(const char* username, const char* oldPassword, const char* newPassword) {
    if (strcmp(username, "") == 0 || strcmp(oldPassword, "") == 0) {
        printf("Error: Username or old password cannot be empty.\n");
        return false;
    }

    if (!checkUsername(username)) {
        printf("Error: Invalid username. Username can only contain lowercase letters and digits.\n");
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
 * @name displayAdmin
 * @brief Display all admins
 * @details This function displays all admins in the `adminHead` linkedlist.
 *
 * @post If the `adminHead` linkedlist is not empty,
 * the function displays all admins in the linkedlist.
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
 * @name freeAdmin
 * @brief Free admin list
 * @details This function frees the memory allocated for the `adminHead` linkedlist.
 *
 * @post The memory allocated for the `adminHead` linkedlist is freed.
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
