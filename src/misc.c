/*!
 * @file misc.c
 *
 * @brief Misc source file
 * @details This file contains the implementation of the functions for the misc module.
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
#include "../include/misc.h"

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
void displayWelcomeMessage(void) {
    FILE* file = fopen("resources/assets/misc/cc.txt", "r");
    if (!file) {
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

/*!
 * @name displayUserMenu
 * @brief Display user menu
 * @details This function displays the user menu.
 *
 * @post The user menu is displayed.
 */
void displayUserMenu(void) {
    printf("\n--- CrimsonCare Blood Bank Management System (User) ---\n");
    printf("1. Buy Blood\n");
    printf("2. Sell Blood\n");
    printf("3. Display Blood Stocks\n");
    printf("4. Admin Panel\n");
    printf("5. Exit\n");
    printf("Select an option: ");
}

/*!
 * @name displayAdminMenu
 * @brief Display admin menu
 * @details This function displays the admin menu.
 *
 * @post The admin menu is displayed.
 */
void displayAdminMenu(void) {
    printf("\n--- CrimsonCare Blood Bank Management System (Admin) ---\n");
    printf("1. Add Hospital\n");
    printf("2. Update Blood Quantity\n");
    printf("3. Update Blood Price\n");
    printf("4. Change Admin Password\n");
    printf("5. Add Admin\n");
    printf("6. Delete Admin\n");
    printf("7. Delete Hospital\n");
    printf("8. Display Admins\n");
    printf("9. Display Hospitals\n");
    printf("10. Display Blood Stocks\n");
    printf("11. Display Transactions\n");
    printf("12. Exit\n");
    printf("Select an option: ");
}

/*!
 * @name clearInputBuffer
 * @brief Clear input buffer
 * @details This function clears the input buffer
 * by reading until a newline character is encountered.
 *
 * @post The input buffer is cleared.
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
bool checkUsername(const char* str) {
    while (*str) {
        if (!(*str >= 'a' && *str <= 'z') && !(*str >= '0' && *str <= '9')) {
            return false;
        }
        str++;
    }
    return true;
}

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
bool containsPipe(const char* str) {
    while (*str) {
        if (*str == '|') {
            return true;
        }
        str++;
    }
    return false;
}

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
void getPassword(char* password, size_t size) {
#ifdef _WIN32
    size_t i = 0;
    char ch;
    while (i < size - 1) {

        ch = getch();

        if (ch == '\r') {

            break;
        } else if (ch == '\b') {

            if (i > 0) {
                i--;
                printf("\b \b");

            }
        } else {
            password[i++] = ch;
            printf("*");

        }
    }
    password[i] = '\0';

    printf("\n");
#else

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    newt.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fgets(password, size);
    password[strcspn(password, "\n")] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    printf("\n");
#endif
}

/*!
 * @name isLeapYear
 * @brief Check if year is leap year
 * @details This function checks if a year is a leap year.
 *
 * @param[in] year Year to check
 *
 * @return True if year is leap year, False otherwise
 */
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

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
bool isValidDate(const char* date) {
    if (strcmp(date, "") == 0) {
        printf("Error: Date cannot be empty.\n");
        return false;
    }

    int year, month, day;

    if (strlen(date) < 8 || strlen(date) > 10) {
        printf("Error: Invalid date format.\n");
        return false;
    }

    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
        printf("Error: Invalid date format.\n");
        return false;
    }

    if (month < 1 || month > 12) {
        printf("Error: Invalid month.\n");
        return false;
    }

    int daysInMonth[] = { 31, 28 + (int)isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (day < 1 || day > daysInMonth[month - 1]) {
        printf("Error: Invalid day.\n");
        return false;
    }

    return true;
}

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
void formatDate(char* date) {
    if (strcmp(date, "") == 0) {
        printf("Error: Date cannot be empty.\n");
        return;
    }

    if (!isValidDate(date)) {
        printf("Error: Invalid date format.\n");
        return;
    }

    int year, month, day;
    sscanf(date, "%d-%d-%d", &year, &month, &day);
    sprintf(date, "%04d-%02d-%02d", year, month, day);
}
