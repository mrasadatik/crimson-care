#ifndef TYPES_H
#define TYPES_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "encryption.h"

typedef struct Flags {
    bool is_active : 1;
    bool is_verified : 1;
    bool is_super_admin : 1;
    uint8_t reserved : 5;
} Flags;

typedef struct BloodGroup {
    char name[8];
    uint16_t quantity;
    float price;
    struct BloodGroup* next;
    struct BloodGroup* prev;
} BloodGroup;

typedef struct Admin {
    char id[16];
    unsigned char password_hash[HASH_LENGTH];
    unsigned char salt[SALT_LENGTH];
    Flags flags;
    struct Admin* next;
    struct Admin* prev;
} Admin;

typedef struct Transaction {
    bool is_purchase;
    char name[32];
    char bloodGroup[8];
    uint16_t quantity;
    time_t timestamp;
    struct Transaction* next;
    struct Transaction* prev;
} Transaction;

typedef struct SystemState {
    BloodGroup* bloodHead;
    Transaction* transactionHead;
    Admin* adminHead;
    uint32_t tokenCounter;
    EncryptionContext encContext;
} SystemState;

#endif
