/*!
 * @file blood_manager.h
 *
 * @brief Blood manager header file
 * @details This file contains the declarations of the functions and structures for the blood manager module.
 *
 * @author CrimsonCare Team
 * @date 2025-01-18
 *
 * @copyright
 * Copyright (c) 2025 CrimsonCare Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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

 /*!
  * @def BLOOD_GROUP_NAME_LENGTH
  * @brief Blood group name length
  * @details This macro defines the length of the blood group name.
  */
#define BLOOD_GROUP_NAME_LENGTH 4

  /*!
   * @struct BloodStock
   * @brief Blood stock structure
   * @details This structure represents a blood stock in the system.
   */
typedef struct BloodStock {
    float price; /*!< Blood price */
    uint32_t id; /*!< Blood group id */
    uint32_t quantity; /*!< Blood quantity */
    char bloodGroup[BLOOD_GROUP_NAME_LENGTH]; /*!< Blood group name */
    struct BloodStock* next; /*!< Next blood stock */
} BloodStock;

/*!
 * @brief Globally exposed blood stock head pointer
 * @details This pointer is used to track blood stock linkedlist on runtime.
 */
extern BloodStock* bloodHead = NULL;

/*!
 * @name isValidBloodGroup
 * @brief Check if blood group is valid
 * @details This function checks if the given blood group id is valid
 * by checking the size of the `availableBloodGroups` array.
 *
 * @param[in] id Blood group id
 *
 * @return True if blood group is valid, False otherwise
 *
 * @post If the @p id is within the range of the `availableBloodGroups` array,
 * the function returns true. Otherwise, it returns false.
 */
bool isValidBloodGroup(uint32_t id);

/*!
 * @name addBloodGroup
 * @brief Add blood group
 * @details This function adds a new blood group to the `bloodHead` linkedlist.
 *
 * @param[in] id Blood group id
 * @param[in] bloodGroup Blood group name
 * @param[in] price Blood group price
 * @param[in] quantity Blood group quantity
 *
 * @return True if blood group is added, False otherwise
 *
 * @pre @p id is valid
 * @pre @p bloodGroup is not empty
 * @post Updates the blood stock in the `bloodHead` linkedlist.
 *
 * @exception If the @p bloodGroup is empty, an error message is displayed.
 * @exception If the @p id is not valid, an error message is displayed.
 * @exception malloc() - If the memory allocation for the new blood group fails, an error message is displayed.
 */
bool addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity);

/*!
 * @name initializeBloodGroups
 * @brief Initialize blood groups
 * @details This function helps to initialize the default blood groups
 * to the `bloodHead` linkedlist.
 *
 * @post The blood groups are added to the `bloodHead` linkedlist.
 *
 * @exception If adding blood group fails, an error message is displayed.
 */
void initializeBloodGroups(void);

/*!
 * @name saveBloodGroups
 * @brief Save blood groups to file
 * @details This function saves the linkedlist data
 * from `bloodHead` to the file `resources/db/blood_data.txt`.
 *
 * @note The file path 'resources/db' is relative to the project root directory.
 * Make sure that the folder exists also to run the program from the root directory.
 *
 * @post The linkedlist data is saved to the file.
 *
 * @exception fopen() - If the file cannot be opened, an error message is displayed.
 */
void saveBloodGroups(void);

/*!
 * @name updateBloodQuantity
 * @brief Update blood quantity
 * @details This function updates the blood quantity of the given blood group id
 * by traversing the `bloodHead` linkedlist.
 *
 * @param[in] id Blood group id
 * @param[in] newQuantity New quantity
 *
 * @return True if blood quantity is updated, False otherwise
 *
 * @post If the @p id is found in the `bloodHead` linkedlist,
 * the function updates the blood quantity and saves the updated linkedlist.
 *
 * @exception If the @p id is not found in the `bloodHead` linkedlist, an error message is displayed.
 */
bool updateBloodQuantity(uint32_t id, uint32_t newQuantity);

/*!
 * @name updateBloodPrice
 * @brief Update blood price
 * @details This function updates the blood price of the given blood group id
 * by traversing the `bloodHead` linkedlist.
 *
 * @param[in] id Blood group id
 * @param[in] newPrice New price
 *
 * @return True if blood price is updated, False otherwise
 *
 * @post If the @p id is found in the `bloodHead` linkedlist,
 * the function updates the blood price and saves the updated linkedlist.
 *
 * @exception If the @p id is not found in the `bloodHead` linkedlist, an error message is displayed.
 */
bool updateBloodPrice(uint32_t id, float newPrice);

/*!
 * @name loadBloodGroups
 * @brief Load blood groups from file
 * @details This function loads the blood groups from the file `resources/db/blood_data.txt`
 * to the `bloodHead` linkedlist.
 *
 * @note The file path 'resources/db' is relative to the project root directory.
 * Make sure that the folder exists also to run the program from the root directory.
 *
 * @post The blood groups are loaded to the `bloodHead` linkedlist.
 *
 * @exception fopen() - If the file cannot be opened, an error message is displayed.
 * @exception malloc() - If the memory allocation for the new blood group fails, an error message is displayed.
 */
void loadBloodGroups(void);

/*!
 * @name isBloodAvailable
 * @brief Check if blood is available for a specific transaction type
 * @details This function checks if blood is available for a specific transaction type
 * by traversing the `bloodHead` linkedlist.
 *
 * @param[in] id Blood group id, null if to check for any blood
 * @param[in] type Transaction type
 *
 * @return True if blood is available, False otherwise
 *
 * @pre @p id is null or valid
 * @pre @p type is BUY or SELL
 * @post If the @p id is found in the `bloodHead` linkedlist,
 * the function returns true. Otherwise, it returns false.
 *
 * @exception If the @p type is not BUY or SELL, an error message is displayed.
 * @exception If the @p id is not null and is not valid, an error message is displayed.
 */
bool isBloodAvailable(uint32_t* id, TransactionType type);

/*!
 * @name displayBloodGroups
 * @brief Display all blood groups
 * @details This function displays all the blood groups in the `availableBloodGroups` array.
 *
 * @post The available blood groups are displayed.
 */
void displayBloodGroups(void);

/*!
 * @name displayBloodStocks
 * @brief Display all blood stocks
 * @details This function displays all the blood stocks in the `bloodHead` linkedlist.
 *
 * @note If Price or Quantity is not available, it is displayed as N/A.
 *
 * @post The blood stocks are displayed.
 */
void displayBloodStocks(void);

/*!
 * @name getBloodGroupById
 * @brief Get blood group by id
 * @details This function returns the blood group name by the given id.
 *
 * @param[in] id Blood group id
 *
 * @return Blood group name or NULL if not found
 *
 * @post If the @p id is valid, the function returns the blood group name.
 *
 * @exception If the @p id is not valid, an error message is displayed.
 */
char* getBloodGroupById(uint32_t id);

/*!
 * @name freeBloodList
 * @brief Free blood list
 * @details This function frees the `bloodHead` linkedlist.
 *
 * @post The `bloodHead` linkedlist is freed.
 */
void freeBloodList(void);

#endif
