#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/transaction_manager.h"
#include "../include/blood_manager.h"

Transaction* transactionHead = NULL;

bool addTransaction(TransactionType type, const char* name, const char* bloodGroup, uint32_t quantity) {

    if (!isBloodGroupAvailable(bloodGroup)) {
        printf("No stock available for blood group: %s\n", bloodGroup);
        return false;
    }

    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));
    if (!newTransaction) {
        printf("Memory allocation failed!\n");
        return false;
    }

    newTransaction->type = type;
    strncpy(newTransaction->name, name, sizeof(newTransaction->name) - 1);
    newTransaction->name[sizeof(newTransaction->name) - 1] = '\0';
    strncpy(newTransaction->bloodGroup, bloodGroup, sizeof(newTransaction->bloodGroup) - 1);
    newTransaction->bloodGroup[sizeof(newTransaction->bloodGroup) - 1] = '\0';
    newTransaction->quantity = quantity;

    if (type == SELL) {
        getchar();
        printf("Enter the date and time of donation (YYYY-MM-DD): ");
        fgets(newTransaction->date, sizeof(newTransaction->date), stdin);
        newTransaction->date[strcspn(newTransaction->date, "\n")] = 0;
    } else {

        BloodStock* stock = bloodHead;
        while (stock != NULL) {
            if (strcmp(stock->bloodGroup, bloodGroup) == 0) {
                if (stock->quantity < quantity) {
                    printf("Not enough stock for blood group: %s. Available quantity: %u\n", bloodGroup, stock->quantity);
                    free(newTransaction);
                    return false;
                }

                stock->quantity -= quantity;
                saveBloodGroups();
                break;
            }
            stock = stock->next;
        }
        time_t now = time(NULL);
        strftime(newTransaction->date, sizeof(newTransaction->date), "%Y-%m-%d", localtime(&now));
    }

    newTransaction->next = NULL;

    if (transactionHead == NULL) {
        transactionHead = newTransaction;
    } else {
        Transaction* temp = transactionHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTransaction;
    }

    printf("Transaction added: %s %s %u\n", (type == BUY ? "Buy" : "Sell"), name, quantity);

    if (type == SELL) {
        printf("Sell token generated for %s: TOKEN_%d\n", name, rand() % 10000);
    }

    logTransaction(type, name, bloodGroup, quantity, newTransaction->date);

    return true;
}

void displayTransactions(void) {
    FILE* file = fopen("resources/db/transactions.log", "r");
    if (!file) {
        return;
    }

    char line[256];
    printf("\nRegistered Transactions:\n");
    while (fgets(line, sizeof(line), file)) {
        TransactionType type;
        char name[50], bloodGroup[10], date[20];
        uint32_t quantity;

        if (sscanf(line, "%[^,],%[^,],%[^,],%u,%[^,\n]",
            (type == BUY ? "Buy" : "Sell"), name, bloodGroup, &quantity, date) == 5) {
            type = (strcmp(name, "Buy") == 0) ? BUY : SELL;
            printf("Type: %s, Entity: %s, Blood Group: %s, Quantity: %u, Date: %s\n",
                (type == BUY ? "Buy" : "Sell"), name, bloodGroup, quantity, date);
        }
    }

    fclose(file);
    printf("Transactions displayed successfully.\n");
}

void logTransaction(TransactionType type, const char* name, const char* bloodGroup, uint32_t quantity, const char* date) {
    FILE* file = fopen("resources/db/transactions.log", "a");
    if (!file) {
        printf("Error logging transaction!\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%u,%s\n", (type == BUY ? "Buy" : "Sell"), name, bloodGroup, quantity, date);
    fclose(file);
    printf("Transaction logged successfully.\n");
}
