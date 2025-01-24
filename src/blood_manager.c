/*!
 * @file blood_manager.c
 *
 * @brief Blood manager source file
 * @details This file contains the implementation of the functions for the blood manager module.
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
#include "../include/blood_manager.h"
#include "../include/transaction_manager.h"

 /*!
  * @brief Blood groups
  */
char* availableBloodGroups[8] = { "A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-" };

/*!
 * @brief Blood stock head to track blood groups on runtime
 */
BloodStock* bloodHead = NULL;

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
bool isValidBloodGroup(uint32_t id) {
    return id <= (sizeof(availableBloodGroups) / sizeof(availableBloodGroups[0]));
}

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
bool addBloodGroup(uint32_t id, const char* bloodGroup, float price, uint32_t quantity) {
    if (strcmp(bloodGroup, "") == 0) {
        printf("Error: Invalid blood group data.\n");
        return false;
    }

    if (!isValidBloodGroup(id)) {
        printf("Error: Invalid blood group id.\n");
        return false;
    }

    BloodStock* newGroup = (BloodStock*)malloc(sizeof(BloodStock));
    if (!newGroup) {
        printf("Error allocating memory for blood group: %s\n", strerror(errno));
        return false;
    }
    strncpy(newGroup->bloodGroup, bloodGroup, BLOOD_GROUP_NAME_LENGTH - 1);
    newGroup->bloodGroup[BLOOD_GROUP_NAME_LENGTH - 1] = '\0';
    newGroup->price = price;
    newGroup->quantity = quantity;
    newGroup->id = id;
    newGroup->next = NULL;

    if (bloodHead == NULL) {
        bloodHead = newGroup;
    } else {
        BloodStock* temp = bloodHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newGroup;
    }
    return true;
}

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
void initializeBloodGroups(void) {
    for (uint8_t i = 0; i < (sizeof(availableBloodGroups) / sizeof(availableBloodGroups[0])); i++) {
        if (!addBloodGroup(i + 1, availableBloodGroups[i], 0.0, 0)) {
            printf("Error: Failed to initialize blood group %s.\n", availableBloodGroups[i]);
        }
    }
}

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
void saveBloodGroups(void) {
    errno = 0;
    FILE* file = fopen("resources/db/blood_data.txt", "w");
    if (!file) {
        if (errno != ENOENT) {
            printf("Error opening blood data file: %s\n", strerror(errno));
            return;
        }
    }

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        fprintf(file, "%u %s %.2f %u\n", temp->id, temp->bloodGroup, temp->price, temp->quantity);
        temp = temp->next;
    }
    fclose(file);
}

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
bool updateBloodQuantity(uint32_t id, uint32_t newQuantity) {
    if (!isValidBloodGroup(id)) {
        printf("Error: Invalid blood group id.\n");
        return false;
    }

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->quantity = newQuantity;
            saveBloodGroups();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

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
bool updateBloodPrice(uint32_t id, float newPrice) {
    if (!isValidBloodGroup(id)) {
        printf("Error: Invalid blood group id.\n");
        return false;
    }

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->price = newPrice;
            saveBloodGroups();
            return true;
        }
        temp = temp->next;
    }
    return false;
}

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
void loadBloodGroups(void) {
    errno = 0;
    FILE* file = fopen("resources/db/blood_data.txt", "r");
    if (!file) {
        if (errno == ENOENT) {
            initializeBloodGroups();
            return;
        } else {
            printf("Error opening blood data file: %s\n", strerror(errno));
            freeBloodList();
            return;
        }
    }

    while (1) {
        BloodStock* newBlood = (BloodStock*)malloc(sizeof(BloodStock));
        if (!newBlood) {
            printf("Error allocating memory for blood group: %s\n", strerror(errno));
            freeBloodList();
            fclose(file);
            return;
        }

        if (fscanf(file, "%u %s %f %u", &newBlood->id, newBlood->bloodGroup, &newBlood->price, &newBlood->quantity) != 4) {
            free(newBlood);
            fclose(file);
            break;
        }

        newBlood->next = NULL;

        if (bloodHead == NULL) {
            bloodHead = newBlood;
        } else {
            BloodStock* temp = bloodHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBlood;
        }
    }

    fclose(file);
}

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
bool isBloodAvailable(uint32_t* id, TransactionType type) {
    if (type != BUY && type != SELL) {
        printf("Error: Invalid transaction type.\n");
        return false;
    }

    if (id != NULL && !isValidBloodGroup(*id)) {
        printf("Error: Invalid blood group id.\n");
        return false;
    }

    BloodStock* temp = bloodHead;
    while (temp != NULL) {
        if (type == BUY) {
            if (id == NULL) {
                if (temp->price > 0 && temp->quantity > 0) {
                    return true;
                }
            } else {
                if (temp->id == *id && temp->price > 0 && temp->quantity > 0) {
                    return true;
                }
            }
        } else {
            if (id == NULL) {
                if (temp->price > 0) {
                    return true;
                }
            } else {
                if (temp->id == *id && temp->price > 0) {
                    return true;
                }
            }
        }
        temp = temp->next;
    }
    return false;
}

/*!
 * @name displayBloodGroups
 * @brief Display all blood groups
 * @details This function displays all the blood groups in the `availableBloodGroups` array.
 *
 * @post The available blood groups are displayed.
 */
void displayBloodGroups(void) {
    for (uint32_t i = 0; i < (sizeof(availableBloodGroups) / sizeof(availableBloodGroups[0])); i++) {
        printf("%u. %s\n", i + 1, availableBloodGroups[i]);
    }
}

/*!
 * @name displayBloodStocks
 * @brief Display all blood stocks
 * @details This function displays all the blood stocks in the `bloodHead` linkedlist.
 *
 * @note If Price or Quantity is not available, it is displayed as N/A.
 *
 * @post The blood stocks are displayed.
 */
void displayBloodStocks(void) {
    BloodStock* temp = bloodHead;
    if (temp == NULL) {
        printf("No blood available.\n");
        return;
    }
    printf("\nAvailable Blood:\n");
    while (temp != NULL) {
        if (temp->price > 0.0) {
            printf("%u. %s, Price: %.2f, Quantity: %u\n", temp->id, temp->bloodGroup, temp->price, temp->quantity);
        } else {
            printf("%u. %s, Price: N/A, Quantity: N/A\n", temp->id, temp->bloodGroup);
        }
        temp = temp->next;
    }
}

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
char* getBloodGroupById(uint32_t id) {
    if (!isValidBloodGroup(id)) {
        printf("Error: Invalid blood group id.\n");
        return NULL;
    }

    return availableBloodGroups[id - 1];
}

/*!
 * @name freeBloodList
 * @brief Free blood list
 * @details This function frees the `bloodHead` linkedlist.
 *
 * @post The `bloodHead` linkedlist is freed.
 */
void freeBloodList(void) {
    BloodStock* current = bloodHead;
    while (current != NULL) {
        BloodStock* temp = current;
        current = current->next;
        free(temp);
    }
    bloodHead = NULL;
}

