#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

/*!
 * @brief Display welcome message
 */
void displayWelcomeMessage(void);

/*!
 * @brief Display user menu
 */
void displayUserMenu(void);

/*!
 * @brief Display admin menu
 */
void displayAdminMenu(void);

/*!
 * @brief Clear input buffer
 */
void clearInputBuffer(void);

/*!
 * @brief Get password
 *
 * @param[in,out] password Password
 * @param[in] size Password size
 */
void getPassword(char* password, size_t size);

/*!
 * @brief Check if year is leap year
 *
 * @param[in] year Year to check
 *
 * @return True if year is leap year, False otherwise
 */
bool isLeapYear(int year);

/*!
 * @brief Check if date is valid
 *
 * @param[in] date Date to check
 *
 * @return True if date is valid, False otherwise
 */
bool isValidDate(const char* date);

/*!
 * @brief Format date to yyyy-mm-dd
 *
 * @param[in,out] date Date to format
 */
void formatDate(char* date);

#endif
