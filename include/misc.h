#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void displayUserMenu(void);
void displayAdminMenu(void);
void getPassword(char* password, size_t size);
void clearInputBuffer(void);
bool isLeapYear(int year);
bool isValidDate(const char* date);
void formatDate(char* date);

#endif
