/*!
 * @file main.c
 *
 * @brief Main source file
 * @details This file contains the implementation of the main function.
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
#include "include/admin_manager.h"
#include "include/hospital_manager.h"
#include "include/blood_manager.h"
#include "include/transaction_manager.h"
#include "include/misc.h"

int main(void) {
    loadBloodGroups();
    loadHospitals();
    loadAdminCredentials();

    displayWelcomeMessage();

    uint32_t choice;
    bool isAdmin = false;
    char currentAdminUsername[MAX_USERNAME_LENGTH];

    while (1) {
        displayUserMenu();

        if (scanf("%u", &choice) != 1) {
            printf("Error: Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
        case 1: {
                TransactionType transactionType = BUY;
                if (!isBloodAvailable(NULL, transactionType)) {
                    printf("No blood available for purchase.\n");
                    break;
                }
                char hospitalCode[MAX_TRANSACTION_NAME_LENGTH];
                uint32_t bloodGroupId;
                uint32_t quantity;
                printf("Enter Entity Name (Hospital Code): ");
                fgets(hospitalCode, sizeof(hospitalCode), stdin);
                hospitalCode[strcspn(hospitalCode, "\n")] = 0;
                if (!validateHospitalCode(hospitalCode)) {
                    printf("Error: Invalid hospital code.\n");
                    break;
                }

                displayBloodStocks();
                printf("Enter Blood Group ID: ");
                scanf("%u", &bloodGroupId);
                clearInputBuffer();
                if (!isValidBloodGroup(bloodGroupId)) {
                    printf("Error: Invalid blood group.\n");
                    break;
                }
                if (!isBloodAvailable(&bloodGroupId, transactionType)) {
                    printf("Blood %s is not available for purchase.\n", getBloodGroupById(bloodGroupId));
                    break;
                }
                printf("Enter Quantity: ");
                scanf("%u", &quantity);
                clearInputBuffer();
                if (addTransaction(transactionType, hospitalCode, bloodGroupId, quantity)) {
                    printf("Transaction successful for %s (%s).\n", getHospitalNameByCode(hospitalCode), hospitalCode);
                } else {
                    printf("Error: Transaction failed.\n");
                }
                break;
            }
        case 2: {
                TransactionType transactionType = SELL;
                if (!isBloodAvailable(NULL, transactionType)) {
                    printf("No blood available for sale.\n");
                    break;
                }
                char donorName[MAX_TRANSACTION_NAME_LENGTH];
                uint32_t bloodGroupId;
                uint32_t quantity;
                printf("Enter Donor Name: ");
                fgets(donorName, sizeof(donorName), stdin);
                donorName[strcspn(donorName, "\n")] = 0;

                displayBloodStocks();
                printf("Enter Blood Group ID: ");
                scanf("%u", &bloodGroupId);
                clearInputBuffer();
                if (!isValidBloodGroup(bloodGroupId)) {
                    printf("Error: Invalid blood group.\n");
                    break;
                }
                if (!isBloodAvailable(&bloodGroupId, transactionType)) {
                    printf("Blood %s is not available for sale.\n", getBloodGroupById(bloodGroupId));
                    break;
                }

                printf("Enter Quantity: ");
                scanf("%u", &quantity);
                clearInputBuffer();
                if (addTransaction(transactionType, donorName, bloodGroupId, quantity)) {
                    printf("Transaction successful for %s.\n", donorName);
                } else {
                    printf("Error: Transaction failed.\n");
                }
                break;
            }
        case 3:
            displayBloodStocks();
            break;
        case 4: {
                char adminPassword[MAX_PASSWORD_LENGTH];
                printf("Enter Admin Username: ");
                fgets(currentAdminUsername, sizeof(currentAdminUsername), stdin);
                currentAdminUsername[strcspn(currentAdminUsername, "\n")] = 0;
                printf("Enter Admin Password: ");
                getPassword(adminPassword, sizeof(adminPassword));

                if (validateAdmin(currentAdminUsername, adminPassword)) {
                    isAdmin = true;
                    printf("Admin %s logged in successfully.\n", currentAdminUsername);

                    while (isAdmin) {
                        displayAdminMenu();

                        if (scanf("%u", &choice) != 1) {
                            printf("Error: Invalid input.\n");
                            clearInputBuffer();
                            continue;
                        }

                        clearInputBuffer();

                        switch (choice) {
                        case 1: {
                                char hospitalName[MAX_HOSPITAL_NAME_LENGTH];
                                char hospitalLocation[MAX_HOSPITAL_LOCATION_LENGTH];
                                printf("Enter Hospital Name: ");
                                fgets(hospitalName, sizeof(hospitalName), stdin);
                                hospitalName[strcspn(hospitalName, "\n")] = 0;
                                printf("Enter Hospital Location: ");
                                fgets(hospitalLocation, sizeof(hospitalLocation), stdin);
                                hospitalLocation[strcspn(hospitalLocation, "\n")] = 0;
                                char* hospitalCode = addHospital(hospitalName, hospitalLocation);
                                if (hospitalCode) {
                                    printf("Hospital %s added successfully by %s.\n", hospitalName, currentAdminUsername);
                                    printf("Hospital Code: %s\n", hospitalCode);
                                } else {
                                    printf("Error: Could not add hospital.\n");
                                }
                                break;
                            }
                        case 2: {
                                displayBloodGroups();
                                uint32_t bloodGroupId;
                                uint32_t newQuantity;
                                printf("Enter Blood Group ID: ");
                                scanf("%u", &bloodGroupId);
                                clearInputBuffer();
                                if (!isValidBloodGroup(bloodGroupId)) {
                                    printf("Error: Invalid blood group.\n");
                                    break;
                                }
                                if (!isBloodAvailable(&bloodGroupId, SELL)) {
                                    float newPrice;
                                    printf("Price for %s is not set.\n", getBloodGroupById(bloodGroupId));
                                    printf("Enter New Price: ");
                                    scanf("%f", &newPrice);
                                    clearInputBuffer();
                                    if (updateBloodPrice(bloodGroupId, newPrice)) {
                                        printf("Blood price for %s updated successfully by %s.\n", getBloodGroupById(bloodGroupId), currentAdminUsername);
                                    } else {
                                        printf("Error: Could not update blood price.\n");
                                    }
                                }
                                printf("Enter New Quantity: ");
                                scanf("%u", &newQuantity);
                                clearInputBuffer();
                                if (updateBloodQuantity(bloodGroupId, newQuantity)) {
                                    printf("Blood quantity for %s updated successfully by %s.\n", getBloodGroupById(bloodGroupId), currentAdminUsername);
                                } else {
                                    printf("Error: Could not update blood quantity.\n");
                                }
                                break;
                            }
                        case 3: {
                                displayBloodGroups();
                                uint32_t bloodGroupId;
                                float newPrice;
                                printf("Enter Blood Group ID: ");
                                scanf("%u", &bloodGroupId);
                                clearInputBuffer();
                                if (!isValidBloodGroup(bloodGroupId)) {
                                    printf("Error: Invalid blood group.\n");
                                    break;
                                }
                                printf("Enter New Price: ");
                                scanf("%f", &newPrice);
                                clearInputBuffer();
                                if (updateBloodPrice(bloodGroupId, newPrice)) {
                                    printf("Blood price for %s updated successfully by %s.\n", getBloodGroupById(bloodGroupId), currentAdminUsername);
                                } else {
                                    printf("Error: Could not update blood price.\n");
                                }
                                break;
                            }
                        case 4: {
                                char adminOldPassword[MAX_PASSWORD_LENGTH];
                                char adminNewPassword[MAX_PASSWORD_LENGTH];
                                printf("Enter Old Password: ");
                                getPassword(adminOldPassword, sizeof(adminOldPassword));
                                printf("Enter New Password: ");
                                getPassword(adminNewPassword, sizeof(adminNewPassword));
                                if (changeAdminPassword(currentAdminUsername, adminOldPassword, adminNewPassword)) {
                                    printf("Password for %s updated successfully.\n", currentAdminUsername);
                                } else {
                                    printf("Error: Could not change admin password.\n");
                                }
                                break;
                            }
                        case 5: {
                                char currentAdminPassword[MAX_PASSWORD_LENGTH];
                                char newAdminUsername[MAX_USERNAME_LENGTH];
                                char newAdminPassword[MAX_PASSWORD_LENGTH];
                                char confirmNewAdminPassword[MAX_PASSWORD_LENGTH];
                                printf("To continue, please enter your (%s) current password: ", currentAdminUsername);
                                getPassword(currentAdminPassword, sizeof(currentAdminPassword));
                                if (validateAdmin(currentAdminUsername, currentAdminPassword)) {
                                    printf("Password verified successfully.\n");
                                } else {
                                    printf("Error: Invalid password.\n");
                                    break;
                                }
                                printf("Enter New Admin Username: ");
                                fgets(newAdminUsername, sizeof(newAdminUsername), stdin);
                                newAdminUsername[strcspn(newAdminUsername, "\n")] = 0;
                                printf("Enter New Admin Password: ");
                                getPassword(newAdminPassword, sizeof(newAdminPassword));
                                printf("Confirm New Admin Password: ");
                                getPassword(confirmNewAdminPassword, sizeof(confirmNewAdminPassword));
                                if (strcmp(newAdminPassword, confirmNewAdminPassword) != 0) {
                                    printf("Error: Passwords do not match.\n");
                                    break;
                                }
                                if (addAdmin(newAdminUsername, newAdminPassword, currentAdminUsername, currentAdminPassword)) {
                                    printf("New admin %s added successfully by %s.\n", newAdminUsername, currentAdminUsername);
                                } else {
                                    printf("Error: Could not add new admin.\n");
                                }
                                break;
                            }
                        case 6: {
                                char delAdminUsername[MAX_USERNAME_LENGTH];
                                char currentAdminPassword[MAX_PASSWORD_LENGTH];
                                printf("To continue, please enter your (%s) current password: ", currentAdminUsername);
                                getPassword(currentAdminPassword, sizeof(currentAdminPassword));
                                if (validateAdmin(currentAdminUsername, currentAdminPassword)) {
                                    printf("Password verified successfully.\n");
                                } else {
                                    printf("Error: Invalid password.\n");
                                    break;
                                }
                                printf("Enter Admin Username to Delete: ");
                                fgets(delAdminUsername, sizeof(delAdminUsername), stdin);
                                delAdminUsername[strcspn(delAdminUsername, "\n")] = 0;
                                if (deleteAdmin(delAdminUsername, currentAdminUsername, currentAdminPassword)) {
                                    printf("Admin %s deleted successfully by %s.\n", delAdminUsername, currentAdminUsername);
                                } else {
                                    printf("Error: Could not delete admin.\n");
                                }
                                break;
                            }
                        case 7: {
                                char delHospitalCode[MAX_HOSPITAL_CODE_LENGTH];
                                char currentAdminPassword[MAX_PASSWORD_LENGTH];
                                printf("To continue, please enter your (%s) current password: ", currentAdminUsername);
                                getPassword(currentAdminPassword, sizeof(currentAdminPassword));
                                if (validateAdmin(currentAdminUsername, currentAdminPassword)) {
                                    printf("Password verified successfully.\n");
                                } else {
                                    printf("Error: Invalid password.\n");
                                    break;
                                }
                                printf("Enter Hospital Code to Delete: ");
                                fgets(delHospitalCode, sizeof(delHospitalCode), stdin);
                                delHospitalCode[strcspn(delHospitalCode, "\n")] = 0;
                                if (deleteHospital(delHospitalCode, currentAdminUsername, currentAdminPassword)) {
                                    printf("Hospital %s deleted successfully by %s.\n", delHospitalCode, currentAdminUsername);
                                } else {
                                    printf("Error: Could not delete hospital.\n");
                                }
                                break;
                            }
                        case 8: {
                                displayAdmin();
                                break;
                            }
                        case 9: {
                                displayHospitals();
                                break;
                            }
                        case 10: {
                                displayBloodStocks();
                                break;
                            }
                        case 11: {
                                displayTransactions();
                                break;
                            }
                        case 12:
                            printf("Exiting admin panel...\n");
                            isAdmin = false;
                            break;
                        default:
                            printf("Error: Invalid option. Please try again.\n");
                        }
                    }
                } else {
                    printf("Error: Invalid admin credentials.\n");
                }
                break;
            }
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Error: Invalid option. Please try again.\n");
        }
        if (choice == 5) {
            break;
        }
    }
    freeAdmin();
    freeHospital();
    freeBloodList();
    return 0;
}
