#ifndef BLOOD_MANAGER_H
#define BLOOD_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "misc.h"

#include "transaction_manager.h"

#define BLOOD_GROUP_NAME_LENGTH 4

/*!
 * @brief Blood stock structure
 */
typedef struct BloodStock {
    float price;
    uint32_t id;
    uint32_t quantity;
    char bloodGroup[BLOOD_GROUP_NAME_LENGTH];
    struct BloodStock* next;
} BloodStock;

/*!
 * @brief Globally exposed blood stock list
 */
extern BloodStock* bloodHead;

/*!
 * @brief Add blood group
 *
 * @param[in] id Blood group id
 * @param[in] bloodGroup Blood group name
 * @param[in] price Blood group price
 * @param[in] quantity Blood group quantity
 *
 * @return True if blood group is added, False otherwise
 */
bool addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity);

/*!
 * @brief Initialize blood groups
 */
void initializeBloodGroups(void);

/*!
 * @brief Save blood groups to file
 */
void saveBloodGroups(void);

/*!
 * @brief Check if blood group is valid
 *
 * @param[in] id Blood group id
 *
 * @return True if blood group is valid, False otherwise
 */
bool isValidBloodGroup(uint32_t id);

/*!
 * @brief Update blood quantity
 *
 * @param[in] id Blood group id
 * @param[in] newQuantity New quantity
 *
 * @return True if blood quantity is updated, False otherwise
 */
bool updateBloodQuantity(uint32_t id, uint32_t newQuantity);

/*!
 * @brief Update blood price
 *
 * @param[in] id Blood group id
 * @param[in] newPrice New price
 *
 * @return True if blood price is updated, False otherwise
 */
bool updateBloodPrice(uint32_t id, float newPrice);

/*!
 * @brief Load blood groups from file
 */
void loadBloodGroups(void);

/*!
 * @brief Check if blood is available for a specific transaction type
 *
 * @param[in] id Blood group id, null if to check for any blood
 * @param[in] type Transaction type
 *
 * @return True if blood is available, False otherwise
 */
bool isBloodAvailable(uint32_t* id, TransactionType type);

/*!
 * @brief Display all blood groups
 */
void displayBloodGroups(void);

/*!
 * @brief Display all blood stocks
 */
void displayBloodStocks(void);

/*!
 * @brief Get blood group by id
 *
 * @param[in] id Blood group id
 *
 * @return Blood group name or NULL if not found
 */
char* getBloodGroupById(uint32_t id);

/*!
 * @brief Free blood list from memory
 */
void freeBloodList(void);

#endif
