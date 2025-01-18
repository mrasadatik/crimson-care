#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include "types.h"

bool logTransaction(SystemState* state, bool is_purchase, const char* name,
                   const char* bloodGroup, uint16_t quantity);
void displayTransactions(const SystemState* state);
bool processBloodPurchase(SystemState* state, const char* bloodGroup,
                         uint16_t quantity, const char* hospitalCode);
bool processBloodDonation(SystemState* state, const char* bloodGroup,
                         const char* donorName);

#endif
