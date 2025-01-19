#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stdbool.h>
#include <stdint.h>


typedef enum TransactionType {
    BUY,
    SELL
} TransactionType;


typedef struct Transaction {
    TransactionType type;
    char name[50];
    char bloodGroup[4];
    uint32_t quantity;
    char date[30];
    struct Transaction* next;
} Transaction;


void displayTransactions(void);
bool addTransaction(TransactionType type, const char* name, const char* bloodGroup, uint32_t quantity);
void logTransaction(TransactionType type, const char* name, const char* bloodGroup, uint32_t quantity, const char* date);

#endif
