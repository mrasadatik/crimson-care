#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef enum TransactionType {
    BUY,
    SELL
} TransactionType;


typedef struct Transaction {
    TransactionType type;
    char name[50];
    uint32_t bloodId;
    uint32_t quantity;
    char date[11];
    char token[12];
    struct Transaction* next;
} Transaction;


void displayTransactions(void);
bool addTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity);
void logTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity, const char* date, const char* token);
void freeTransaction(void);

#endif
