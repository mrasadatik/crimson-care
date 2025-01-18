#ifndef BLOOD_MANAGER_H
#define BLOOD_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include "types.h" // Include types for Blood and BloodStock structures

// Function prototypes for blood-related tasks

// Blood management
bool update_blood_quantity(const char* blood_group_name, uint32_t new_quantity); // Updates the quantity of a specific blood group
bool update_blood_price(const char* blood_group_name, uint32_t new_price);       // Updates the price of a specific blood group
bool load_blood_data(const char* filename);                                       // Loads blood data from a file
bool save_blood_data(const char* filename);                                       // Saves blood data to a file
void free_blood_stock(BloodStock* blood_stock);                                   // Frees memory allocated for a blood stock structure

// Error handling
void handle_blood_error(const char* message);                                     // Handles blood-related errors

#endif // BLOOD_MANAGER_H
