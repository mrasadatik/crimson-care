#ifndef HOSPITAL_MANAGER_H
#define HOSPITAL_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#include "admin_manager.h"

#define MAX_HOSPITAL_NAME_LENGTH 100
#define MAX_HOSPITAL_LOCATION_LENGTH 100
#define MAX_HOSPITAL_CODE_LENGTH 8

/*!
 * @brief Hospital structure
 */
typedef struct Hospital {
    char name[MAX_HOSPITAL_NAME_LENGTH];
    char location[MAX_HOSPITAL_LOCATION_LENGTH];
    char code[MAX_HOSPITAL_CODE_LENGTH];
    struct Hospital* next;
} Hospital;

/*!
 * @brief Load hospitals from file
 */
void loadHospitals(void);

/*!
 * @brief Save hospitals to file
 */
void saveHospitals(void);

/*!
 * @brief Add hospital
 *
 * @param[in] name Hospital name
 * @param[in] location Hospital location
 *
 * @return Hospital code or NULL if hospital is not added
 */
char* addHospital(const char* name, const char* location);

/*!
 * @brief Validate hospital code
 *
 * @param[in] code Hospital code
 *
 * @return True if hospital code is valid, False otherwise
 */
bool validateHospitalCode(const char* code);

/*!
 * @brief Delete hospital
 *
 * @param[in] code Hospital code
 * @param[in] adminUsername Admin username
 * @param[in] adminPassword Admin password
 *
 * @return True if hospital is deleted, False otherwise
 */
bool deleteHospital(const char* code, const char* adminUsername, const char* adminPassword);

/*!
 * @brief Get hospital name by code
 *
 * @param[in] code Hospital code
 *
 * @return Hospital name or NULL if not found
 */
char* getHospitalNameByCode(const char* code);

/*!
 * @brief Display all hospitals
 */
void displayHospitals(void);

/*!
 * @brief Free hospital list from memory
 */
void freeHospital(void);

#endif
