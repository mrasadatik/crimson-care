#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include "types.h" // Include types for Admin structure

// Function prototypes for admin-related tasks

// Admin management
bool add_admin(const char* name, const char* username, const char* password); // Adds a new admin
bool update_password(const char* username, const char* new_password);         // Updates the password for an existing admin
bool load_admins(const char* filename);                                        // Loads admin data from a file
bool save_admins(const char* filename);                                        // Saves admin data to a file
void free_admin(Admin* admin);                                                 // Frees memory allocated for an admin

// Error handling
void handle_admin_error(const char* message);                                  // Handles admin-related errors

#endif // ADMIN_MANAGER_H
