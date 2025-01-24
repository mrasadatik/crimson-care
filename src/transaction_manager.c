/*!
 * @file transaction_manager.c
 *
 * @brief Transaction manager source file
 * @details This file contains the implementation of the functions for the transaction manager module.
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
#include "../include/blood_manager.h"
#include "../include/transaction_manager.h"
#include "../include/misc.h"
#include "../include/hospital_manager.h"

 /*!
  * @name logTransaction
  * @brief Log transaction to file
  * @details This function logs a transaction to the file `resources/db/transactions.log`.
  *
  * @param[in] type Transaction type
  * @param[in] name Hospital name
  * @param[in] bloodId Blood group id
  * @param[in] quantity Blood quantity
  * @param[in] date Transaction date
  * @param[in] token Transaction token
  *
  * @return True if transaction is logged, False otherwise
  *
  * @note The file path 'resources/db' is relative to the project root directory.
  * Make sure that the folder exists also to run the program from the root directory.
  *
  * @pre @p type is either BUY or SELL
  * @pre @p name is not empty
  * @pre @p bloodId is a valid blood group id
  * @pre @p quantity is greater than 0
  * @pre @p date is a valid date
  * @post The transaction is logged to the file `resources/db/transactions.log`.
  *
  * @exception If the file `resources/db/transactions.log` cannot be opened,
  * an error message is displayed.
  * @exception If the @p type is not BUY or SELL, an error message is displayed.
  * @exception If the @p name is empty, an error message is displayed.
  * @exception If the @p bloodId is not a valid blood group id, an error message is displayed.
  * @exception If the @p quantity is less than or equal to 0, an error message is displayed.
  * @exception If the @p date is not a valid date, an error message is displayed.
  */
bool logTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity, const char* date, const char* token) {
    errno = 0;
    FILE* file = fopen("resources/db/transactions.log", "a");
    if (!file) {
        if (errno != ENOENT) {
            printf("Error opening transaction log file: %s\n", strerror(errno));
        }
        return false;
    }

    if (type != BUY && type != SELL) {
        printf("Error: Invalid transaction type.\n");
        return false;
    }

    if (!isValidBloodGroup(bloodId)) {
        printf("Error: Invalid blood group.\n");
        return false;
    }

    if (strcmp(name, "") == 0 || quantity <= 0) {
        printf("Error: Invalid transaction parameters.\n");
        return false;
    }

    if (!isValidDate(date)) {
        printf("Error: Invalid date format.\n");
        return false;
    }

    if (token) {
        fprintf(file, "%s|%s|%u|%u|%s|%s\n", (type == BUY ? "Buy" : "Sell"), name, bloodId, quantity, date, token);
    } else {
        fprintf(file, "%s|%s|%u|%u|%s\n", (type == BUY ? "Buy" : "Sell"), name, bloodId, quantity, date);
    }

    fclose(file);
    return true;
}

/*!
 * @name addTransaction
 * @brief Add transaction
 * @details This function adds a transaction to the `transactionHead` linkedlist.
 *
 * @param[in] type Transaction type
 * @param[in] name Hospital name
 * @param[in] bloodId Blood group id
 * @param[in] quantity Blood quantity
 *
 * @return True if transaction is added, False otherwise
 *
 * @note For SELL transaction, the user is asked to enter the date of donation,
 * and a token is generated for the transaction.
 *
 * @pre @p name is not empty
 * @pre @p type is either BUY or SELL
 * @pre @p quantity is greater than 0
 * @pre @p bloodId is a valid blood group id
 * @post The transaction is logged to the file `resources/db/transactions.log` through `logTransaction` function.
 *
 * @exception If the @p name is empty, an error message is displayed.
 * @exception If the @p type is not BUY or SELL, an error message is displayed.
 * @exception If the @p quantity is less than or equal to 0, an error message is displayed.
 * @exception If the @p bloodId is not a valid blood group id, an error message is displayed.
 * @exception For BUY transaction, if the @p name is not a valid hospital code, an error message is displayed.
 * @exception For SELL transaction, if the input date is not a valid date, an error message is displayed.
 */
bool addTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity) {
    if (strcmp(name, "") == 0 || quantity <= 0) {
        printf("Error: Invalid transaction parameters.\n");
        return false;
    }

    if (type != BUY && type != SELL) {
        printf("Error: Invalid transaction type.\n");
        return false;
    }

    if (!isBloodAvailable(&bloodId, type)) {
        printf("No stock available for blood group: %s\n", getBloodGroupById(bloodId));
        return false;
    }

    if (type == BUY) {
        if (!validateHospitalCode(name)) {
            printf("Error: Invalid hospital code.\n");
            return false;
        }
    }

    char date[MAX_TRANSACTION_DATE_LENGTH];
    char token[MAX_TRANSACTION_TOKEN_LENGTH] = "";

    if (type == SELL) {
        printf("Enter the date and time of donation (YYYY-MM-DD): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = 0;
        if (!isValidDate(date)) {
            printf("Error: Invalid date format.\n");
            return false;
        }
        formatDate(date);
    } else {
        BloodStock* stock = bloodHead;
        while (stock != NULL) {
            if (stock->id == bloodId) {
                if (stock->quantity < quantity) {
                    printf("Not enough stock for blood group: %s. Available quantity: %u\n", getBloodGroupById(bloodId), stock->quantity);
                    return false;
                }

                stock->quantity -= quantity;
                saveBloodGroups();
                break;
            }
            stock = stock->next;
        }
        time_t now = time(NULL);
        strftime(date, sizeof(date), "%Y-%m-%d", localtime(&now));
    }

    if (type == SELL) {
        srand(time(NULL));
        sprintf(token, "TOKEN_%d", rand() % 10000);
        printf("Sell token generated for %s: %s\n", name, token);
    }

    if (!logTransaction(type, name, bloodId, quantity, date, type == SELL ? token : NULL)) {
        return false;
    }

    return true;
}

/*!
 * @brief Display all transactions
 * @details This function displays all transactions from the file `resources/db/transactions.log`.
 *
 * @pre The file `resources/db/transactions.log` exists.
 * @post All transactions are displayed.
 *
 * @exception If the file `resources/db/transactions.log` cannot be opened, an error message is displayed.
 */
void displayTransactions(void) {
    errno = 0;
    FILE* file = fopen("resources/db/transactions.log", "r");
    if (!file) {
        if (errno == ENOENT) {
            printf("No registered transactions found.\n");
        } else {
            printf("Error opening transaction log file: %s\n", strerror(errno));
        }
        return;
    }

    char line[256];
    bool hasLogs = false;
    bool firstLog = true;
    char prevLine[256] = { 0 };

    while (fgets(line, sizeof(line), file) != NULL) {
        char type[MAX_TRANSACTION_TOKEN_LENGTH] = "";
        char name[MAX_TRANSACTION_TOKEN_LENGTH] = "";
        uint32_t bloodId = 0;
        uint32_t quantity = 0;
        char date[MAX_TRANSACTION_TOKEN_LENGTH] = "";
        char token[MAX_TRANSACTION_TOKEN_LENGTH] = "";

        if (firstLog) {
            printf("\nRegistered Transactions:\n");
            firstLog = false;
        }

        if (sscanf(line, "%[^|]|%[^|]|%u|%u|%[^|]|%[^|\n]",
            type,
            name,
            &bloodId,
            &quantity,
            date,
            token) >= 5) {

            hasLogs = true;

            if (prevLine[0] != '\0') {
                printf("\t----------------------------------\n");
            }

            printf("\tType: %s\n"
                "\tEntity: %s\n"
                "\tBlood Group: %s\n"
                "\tQuantity: %u\n"
                "\tDate: %s",
                type,
                name,
                getBloodGroupById(bloodId),
                quantity,
                date);

            if (token[0] != '\0') {
                printf("\n\tToken: %s\n", token);
            }

            strncpy(prevLine, line, sizeof(prevLine) - 1);
            prevLine[sizeof(prevLine) - 1] = '\0';
        }
    }

    if (!hasLogs) {
        printf("No registered transactions found.\n");
    }

    fclose(file);
}
