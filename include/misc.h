/*!
 * @file misc.h
 *
 * @brief Misc header file
 * @details This file contains the declarations of the functions for the misc module.
 *
 * @author CrimsonCare Team
 * @date 2025-01-22
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
  * @name displayWelcomeMessage
  * @brief Display welcome message
  * @details This function displays the welcome message
  * by reading from the file `resources/assets/misc/cc.txt`.
  *
  * @note The file `resources/assets/misc/cc.txt` is a text file
  * that contains the welcome message.
  *
  * @pre The file `resources/assets/misc/cc.txt` exists.
  *
  * @post The welcome message is displayed.
  */
void displayWelcomeMessage(void);

/*!
 * @name displayUserMenu
 * @brief Display user menu
 * @details This function displays the user menu.
 *
 * @post The user menu is displayed.
 */
void displayUserMenu(void);

/*!
 * @name displayAdminMenu
 * @brief Display admin menu
 * @details This function displays the admin menu.
 *
 * @post The admin menu is displayed.
 */
void displayAdminMenu(void);

/*!
 * @name clearInputBuffer
 * @brief Clear input buffer
 * @details This function clears the input buffer
 * by reading until a newline character is encountered.
 *
 * @post The input buffer is cleared.
 */
void clearInputBuffer(void);

/*!
 * @name checkUsername
 * @brief Check if username is valid
 * @details This function checks if a username is valid.
 *
 * @param[in] str Username to check
 *
 * @return True if username is valid, False otherwise
 *
 * @note Username can only contain lowercase letters and digits.
 *
 * @pre @p str is not empty
 * @post If the @p str is valid, the function returns true.
 * Otherwise, it returns false.
 */
bool checkUsername(const char* str);


/*!
 * @name containsPipe
 * @brief Check if string contains pipe
 * @details This function checks if a string contains a pipe character.
 *
 * @param[in] str String to check
 *
 * @return True if string contains pipe, False otherwise
 *
 * @pre @p str is not empty
 * @post If the @p str contains a pipe character, the function returns true.
 * Otherwise, it returns false.
 */
bool containsPipe(const char* str);

/*!
 * @name getPassword
 * @brief Get password
 * @details This function gets the password from the user
 * by reading from the standard input.
 *
 * @param[in,out] password Password
 * @param[in] size Password size
 *
 * @post Updates the @p password with the user's input
 * through the pointer @p password.
 */
void getPassword(char* password, size_t size);

/*!
 * @name isLeapYear
 * @brief Check if year is leap year
 * @details This function checks if a year is a leap year.
 *
 * @param[in] year Year to check
 *
 * @return True if year is leap year, False otherwise
 */
bool isLeapYear(int year);

/*!
 * @name isValidDate
 * @brief Check if date is valid
 * @details This function checks if a date is valid.
 *
 * @param[in] date Date to check
 *
 * @return True if date is valid, False otherwise
 *
 * @pre @p date is not empty
 * @post If the @p date is valid, the function returns true.
 * Otherwise, it returns false.
 *
 * @exception If the @p date is empty, an error message is displayed.
 * @exception If the @p date is invalid, an error message is displayed.
 */
bool isValidDate(const char* date);

/*!
 * @name formatDate
 * @brief Format date to yyyy-mm-dd
 * @details This function formats a date string to the format yyyy-mm-dd.
 *
 * @param[in,out] date Date to format
 *
 * @pre @p date is not empty
 * @post The @p date is formatted to the format yyyy-mm-dd and updates the @p date through the pointer @p date.
 *
 * @exception If the @p date is empty, an error message is displayed.
 * @exception If the @p date is invalid, an error message is displayed.
 */
void formatDate(char* date);

#endif
