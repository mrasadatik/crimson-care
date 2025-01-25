/*!
 * @file admin_manager.h
 *
 * @brief Admin manager header file
 * @details This file contains the declarations of the functions and structures for the admin manager module.
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
#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

 /*!
  * @def MAX_USERNAME_LENGTH
  * @brief Maximum username length
  * @details This macro defines the maximum length of the username.
  */
#define MAX_USERNAME_LENGTH 20

  /*!
   * @def MAX_PASSWORD_LENGTH
   * @brief Maximum password length
   * @details This macro defines the maximum length of the password.
   */
#define MAX_PASSWORD_LENGTH 20

   /*!
    * @struct Admin
    * @brief Admin structure
    * @details This structure represents an admin user in the system.
    */
typedef struct Admin {
    char username[MAX_USERNAME_LENGTH]; /*!< Admin username */
    char password[MAX_PASSWORD_LENGTH]; /*!< Admin password */
    struct Admin* next; /*!< Next admin */
} Admin;

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
void saveAdminCredentials(void);

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
void loadAdminCredentials(void);

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
bool adminExists(const char* username);

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
bool validateAdmin(const char* username, const char* password);

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
bool addAdmin(const char* username, const char* password, const char* currentAdminUsername, const char* currentAdminPassword);

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
bool deleteAdmin(const char* username, const char* currentAdminUsername, const char* currentAdminPassword);

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
bool changeAdminPassword(const char* username, const char* oldPassword, const char* newPassword);

/*!
 * @name displayAdmin
 * @brief Display all admins
 * @details This function displays all admins in the `adminHead` linkedlist.
 *
 * @post If the `adminHead` linkedlist is not empty,
 * the function displays all admins in the linkedlist.
 */
void displayAdmin(void);

/*!
 * @name freeAdmin
 * @brief Free admin list
 * @details This function frees the memory allocated for the `adminHead` linkedlist.
 *
 * @post The memory allocated for the `adminHead` linkedlist is freed.
 */
void freeAdmin(void);

#endif

