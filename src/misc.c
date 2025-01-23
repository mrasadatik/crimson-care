#include "../include/misc.h"

/*!
 * @brief Display welcome message
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
 * @brief Display user menu
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
 * @brief Display admin menu
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
 * @brief Clear input buffer
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*!
 * @brief Get password
 *
 * @param[in,out] password Password
 * @param[in] size Password size
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
 * @brief Check if year is leap year
 *
 * @param[in] year Year to check
 *
 * @return True if year is leap year, False otherwise
 */
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*!
 * @brief Check if date is valid
 *
 * @param[in] date Date to check
 *
 * @return True if date is valid, False otherwise
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
 * @brief Format date to yyyy-mm-dd
 *
 * @param[in,out] date Date to format
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
