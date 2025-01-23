#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_TRANSACTION_NAME_LENGTH 50
#define MAX_TRANSACTION_DATE_LENGTH 11
#define MAX_TRANSACTION_TOKEN_LENGTH 12

/*!
 * @brief Transaction type enum
 */
typedef enum TransactionType {
    SELL,
    BUY
} TransactionType;


/*!
 * @brief Transaction structure
 */
typedef struct Transaction {
    uint32_t bloodId;
    uint32_t quantity;
    TransactionType type;
    char name[MAX_TRANSACTION_NAME_LENGTH];
    char date[MAX_TRANSACTION_DATE_LENGTH];
    char token[MAX_TRANSACTION_TOKEN_LENGTH];
    struct Transaction* next;
} Transaction;

/*!
 * @brief Log transaction to file
 *
 * @param[in] type Transaction type
 * @param[in] name Hospital name
 * @param[in] bloodId Blood group id
 * @param[in] quantity Blood quantity
 * @param[in] date Transaction date
 * @param[in] token Transaction token
 */
void logTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity, const char* date, const char* token);

/*!
 * @brief Add transaction
 *
 * @param[in] type Transaction type
 * @param[in] name Hospital name
 * @param[in] bloodId Blood group id
 * @param[in] quantity Blood quantity
 *
 * @return True if transaction is added, False otherwise
 */
bool addTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity);

/*!
 * @brief Display all transactions
 */
void displayTransactions(void);

/*!
 * @brief Free transaction list from memory
 */
void freeTransaction(void);

#endif
