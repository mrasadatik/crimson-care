#include "../include/transaction_manager.h"
#include "../include/blood_manager.h"
#include "../include/misc.h"
#include "../include/hospital_manager.h"

Transaction* transactionHead = NULL;

bool addTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity) {
    errno = 0;
    if (strcmp(name, "") == 0 || quantity <= 0) {
        errno = EINVAL;
        perror("Error");
        return false;
    }

    if (!isBloodAvailable(bloodId, type)) {
        printf("No stock available for blood group: %s\n", getBloodGroupById(bloodId));
        return false;
    }

    if (type == BUY) {
        if (!validateHospitalCode(name)) {
            printf("Invalid hospital code.\n");
            return false;
        }
    }

    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));
    if (!newTransaction) {
        perror("Error");
        return false;
    }

    newTransaction->type = type;
    strncpy(newTransaction->name, name, sizeof(newTransaction->name) - 1);
    newTransaction->name[sizeof(newTransaction->name) - 1] = '\0';
    newTransaction->bloodId = bloodId;
    newTransaction->quantity = quantity;

    if (type == SELL) {
        printf("Enter the date and time of donation (YYYY-MM-DD): ");
        fgets(newTransaction->date, sizeof(newTransaction->date), stdin);
        newTransaction->date[strcspn(newTransaction->date, "\n")] = 0;
        if (!isValidDate(newTransaction->date)) {
            return false;
        }
        formatDate(newTransaction->date);
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

    if (type == SELL) {
        srand(time(NULL));
        sprintf(newTransaction->token, "TOKEN_%d", rand() % 10000);
        printf("Sell token generated for %s: %s\n", name, newTransaction->token);
        logTransaction(type, name, bloodId, quantity, newTransaction->date, newTransaction->token);
    } else {
        logTransaction(type, name, bloodId, quantity, newTransaction->date, NULL);
    }

    return true;
}

void displayTransactions(void) {
    errno = 0;
    FILE* file = fopen("resources/db/transactions.log", "r");
    if (!file) {
        if (errno == ENOENT) {
            printf("No registered transactions found.\n");
        } else {
            perror("Error");
        }
        return;
    }

    char line[256];
    bool hasLogs = false;
    bool firstLog = true;
    char prevLine[256] = { 0 };

    while (fgets(line, sizeof(line), file)) {
        Transaction transaction = { 0 };

        if (firstLog) {
            printf("\nRegistered Transactions:\n");
            firstLog = false;
        }

        char type[5];

        if (sscanf(line, "%[^,],%[^,],%u,%u,%[^,],%[^,\n]",
            type,
            transaction.name,
            &transaction.bloodId,
            &transaction.quantity,
            transaction.date,
            transaction.token) >= 5) {

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
                transaction.name,
                getBloodGroupById(transaction.bloodId),
                transaction.quantity,
                transaction.date);

            if (transaction.token[0] != '\0') {
                printf("\n\tToken: %s\n", transaction.token);
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

void logTransaction(TransactionType type, const char* name, uint32_t bloodId, uint32_t quantity, const char* date, const char* token) {
    errno = 0;
    FILE* file = fopen("resources/db/transactions.log", "a");
    if (!file) {
        if (errno == ENOENT) {
            printf("No registered transactions found.\n");
        } else {
            perror("Error");
        }
        return;
    }

    if (token) {
        fprintf(file, "%s,%s,%u,%u,%s,%s\n", (type == BUY ? "Buy" : "Sell"), name, bloodId, quantity, date, token);
    } else {
        fprintf(file, "%s,%s,%u,%u,%s\n", (type == BUY ? "Buy" : "Sell"), name, bloodId, quantity, date);
    }

    fclose(file);
}

void freeTransaction(void) {
    Transaction* current = transactionHead;
    while (current != NULL) {
        Transaction* temp = current;
        current = current->next;
        free(temp);
    }
    transactionHead = NULL;
}
