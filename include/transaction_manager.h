#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include "types.h" // Include types for Transaction structure

// Function prototypes for transaction-related tasks

// Transaction management
bool record_transaction(const Transaction* transaction); // Records a new transaction
bool load_transactions(const char* filename);           // Loads transactions from a file
bool save_transactions(const char* filename);           // Saves transactions to a file
void free_transaction(Transaction* transaction);         // Frees memory allocated for a transaction

// Error handling
void handle_transaction_error(const char* message);     // Handles transaction-related errors

#endif // TRANSACTION_MANAGER_H
