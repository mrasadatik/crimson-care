/*!
 * @file transaction_manager.h
 *
 * @brief Transaction manager header file
 * @details This file contains the declarations of the functions and structures for the transaction manager module.
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
#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

 /*!
 * @def MAX_TRANSACTION_NAME_LENGTH
 * @brief Maximum transaction name length
 * @details This macro defines the maximum length of the transaction name.
 */
#define MAX_TRANSACTION_NAME_LENGTH 50

 /*!
 * @def MAX_TRANSACTION_DATE_LENGTH
 * @brief Maximum transaction date length
 * @details This macro defines the maximum length of the transaction date.
 */
#define MAX_TRANSACTION_DATE_LENGTH 11

 /*!
 * @def MAX_TRANSACTION_TOKEN_LENGTH
 * @brief Maximum transaction token length
 * @details This macro defines the maximum length of the transaction token.
 */
#define MAX_TRANSACTION_TOKEN_LENGTH 12

 /*!
 * @enum TransactionType
 * @brief Transaction type enum
 * @details This enum defines the transaction type.
 */
typedef enum TransactionType {
    SELL, /*!< Sell transaction type */
    BUY /*!< Buy transaction type */
} TransactionType;

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
bool logTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity, const char* date, const char* token);

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
 */
bool addTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity);


/*!
 * @brief Display all transactions
 * @details This function displays all transactions from the file `resources/db/transactions.log`.
 *
 * @pre The file `resources/db/transactions.log` exists.
 * @post All transactions are displayed.
 *
 * @exception If the file `resources/db/transactions.log` cannot be opened, an error message is displayed.
 */
void displayTransactions(void);

/*!
 * @brief Free transaction list from memory
 */
void freeTransaction(void);

#endif
