#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Function prototypes for system interactions

// Memory management
void* allocate_memory(size_t size); // Allocates memory of given size
void free_memory(void* ptr);          // Frees allocated memory

// Input handling
void clear_input_buffer(void);         // Clears the input buffer

// File operations
bool load_from_file(const char* filename, void* data, size_t data_size); // Loads data from a file
bool save_to_file(const char* filename, const void* data, size_t data_size); // Saves data to a file

// Error handling
void handle_error(const char* message); // Handles errors by printing a message and exiting

#endif // SYSTEM_MANAGER_H
