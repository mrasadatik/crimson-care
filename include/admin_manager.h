#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

/*!
 * @brief Admin structure
 */
typedef struct Admin {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    struct Admin* next;
} Admin;

/*!
 * @brief Save admin credentials to file
 */
void saveAdminCredentials(void);

/*!
 * @brief Load admin credentials from file
 */
void loadAdminCredentials(void);

/*!
 * @brief Check if admin exists
 *
 * @param[in] username Admin username
 *
 * @return True if admin exists, False otherwise
 */
bool adminExists(const char* username);

/*!
 * @brief Validate admin credentials
 *
 * @param[in] username Admin username
 * @param[in] password Admin password
 *
 * @return True if credentials are valid, False otherwise
 */
bool validateAdmin(const char* username, const char* password);

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
bool addAdmin(const char* username, const char* password, const char* currentAdminUsername, const char* currentAdminPassword);

/*!
 * @brief Delete admin
 *
 * @param[in] username Admin username
 *
 * @return True if admin is deleted, False otherwise
 */
bool deleteAdmin(const char* username, const char* currentAdminUsername, const char* currentAdminPassword);

/*!
 * @brief Change admin password
 *
 * @param[in] username Admin username
 * @param[in] oldPassword Old password
 * @param[in] newPassword New password
 *
 * @return True if password is changed, False otherwise
 */
bool changeAdminPassword(const char* username, const char* oldPassword, const char* newPassword);

/*!
 * @brief Display all admins
 */
void displayAdmin(void);

/*!
 * @brief Free admin list from memory
 */
void freeAdmin(void);

#endif

