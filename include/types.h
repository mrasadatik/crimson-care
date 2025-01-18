#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

// Error codes
typedef enum {
    SUCCESS = 0,
    ERR_INVALID_INPUT = EINVAL,
    ERR_NOT_FOUND = ENOENT,
    ERR_MEMORY_ALLOCATION = ENOMEM,
    ERR_PERMISSION_DENIED = EACCES,
} ErrorCode;

// Blood structure
typedef struct {
    char name[3];               // Blood group name (e.g., "A+", "B-")
} BloodGroup;

// Blood stock structure
typedef struct {
    BloodGroup blood_group;                // Blood group information
    uint32_t quantity;          // Available quantity of this blood group
    uint32_t price;             // Price in cents for this blood group
} BloodStock;

// Transaction structure
typedef struct {
    uint32_t id;                // Auto-incremented unique identifier for the transaction
    char type;                  // 'b' for buy, 's' for sell
    char entity[64];            // Hospital code or donor name
    BloodGroup blood_group;    // Blood group (e.g., "A+", "B-")
    uint32_t quantity;          // Amount of blood purchased or donated
    char date_time[20];         // Timestamp of the transaction (YYYY-MM-DD HH:MM:SS)
} Transaction;

// Admin structure
typedef struct {
    char name[64];              // Name of the admin
    char username[32];          // Unique username for the admin
    char password[64];          // Hashed password
} Admin;

// Hospital structure
typedef struct {
    char code[8];              // Unique hospital code
    char name[64];              // Hospital name
    char location[64];          // Hospital location
} Hospital;

#endif // TYPES_H
