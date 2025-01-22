#include "include/admin_manager.h"
#include "include/hospital_manager.h"
#include "include/blood_manager.h"
#include "include/transaction_manager.h"
#include "include/misc.h"

int main(void) {
    loadBloodGroups();
    loadHospitals();
    loadAdminCredentials();

    uint32_t choice;
    bool isAdmin = false;

    while (1) {
        displayUserMenu();

        if (scanf("%u", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
        case 1: {
                if (!isAnyBloodAvailable(BUY)) {
                    printf("No blood available for purchase.\n");
                    break;
                }
                Transaction transaction;
                transaction.type = BUY;
                printf("Enter Entity Name (Hospital Code): ");
                fgets(transaction.name, sizeof(transaction.name), stdin);
                transaction.name[strcspn(transaction.name, "\n")] = 0;
                if (!validateHospitalCode(transaction.name)) {
                    printf("Invalid hospital code.\n");
                    break;
                }

                displayBloodStocks();
                printf("Enter Blood Group ID: ");
                scanf("%u", &transaction.bloodId);
                clearInputBuffer();
                if (!isValidBloodGroup(transaction.bloodId)) {
                    printf("Invalid blood group.\n");
                    break;
                }
                if (!isBloodAvailable(transaction.bloodId, BUY)) {
                    printf("Blood %s is not available for purchase.\n", getBloodGroupById(transaction.bloodId));
                    break;
                }
                printf("Enter Quantity: ");
                scanf("%u", &transaction.quantity);
                clearInputBuffer();
                if (addTransaction(transaction.type, transaction.name, transaction.bloodId, transaction.quantity)) {
                    printf("Transaction successful.\n");
                }
                break;
            }
        case 2: {
                if (!isAnyBloodAvailable(SELL)) {
                    printf("No blood available for sale.\n");
                    break;
                }
                Transaction transaction;
                transaction.type = SELL;
                printf("Enter Donor Name: ");
                fgets(transaction.name, sizeof(transaction.name), stdin);
                transaction.name[strcspn(transaction.name, "\n")] = 0;

                displayBloodStocks();
                printf("Enter Blood Group ID: ");
                scanf("%u", &transaction.bloodId);
                clearInputBuffer();
                if (!isValidBloodGroup(transaction.bloodId)) {
                    printf("Invalid blood group.\n");
                    break;
                }
                if (!isBloodAvailable(transaction.bloodId, SELL)) {
                    printf("Blood %s is not available for sale.\n", getBloodGroupById(transaction.bloodId));
                    break;
                }

                printf("Enter Quantity: ");
                scanf("%u", &transaction.quantity);
                clearInputBuffer();
                if (addTransaction(transaction.type, transaction.name, transaction.bloodId, transaction.quantity)) {
                    printf("Transaction successful.\n");
                }
                break;
            }
        case 3:
            displayBloodStocks();
            break;
        case 4: {
                Admin admin;
                printf("Enter Admin Username: ");
                fgets(admin.username, sizeof(admin.username), stdin);
                admin.username[strcspn(admin.username, "\n")] = 0;
                getPassword(admin.password, sizeof(admin.password));

                if (validateAdmin(admin.username, admin.password)) {
                    isAdmin = true;
                    printf("Admin logged in successfully.\n");

                    while (isAdmin) {
                        displayAdminMenu();

                        if (scanf("%u", &choice) != 1) {
                            printf("Invalid input.\n");
                            clearInputBuffer();
                            continue;
                        }

                        clearInputBuffer();

                        switch (choice) {
                        case 1: {
                                Hospital hospital;
                                printf("Enter Hospital Name: ");
                                fgets(hospital.name, sizeof(hospital.name), stdin);
                                hospital.name[strcspn(hospital.name, "\n")] = 0;
                                printf("Enter Hospital Location: ");
                                fgets(hospital.location, sizeof(hospital.location), stdin);
                                hospital.location[strcspn(hospital.location, "\n")] = 0;
                                if (addHospital(hospital.name, hospital.location)) {
                                    printf("Hospital added successfully.\n");
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
                                    printf("Invalid blood group.\n");
                                    break;
                                }
                                if (!isBloodAvailable(bloodGroupId, SELL)) {
                                    float newPrice;
                                    printf("Price for %s is not set.\n", getBloodGroupById(bloodGroupId));
                                    printf("Enter New Price: ");
                                    scanf("%f", &newPrice);
                                    clearInputBuffer();
                                    if (updateBloodPrice(bloodGroupId, newPrice)) {
                                        printf("Blood price updated successfully.\n");
                                    }
                                }
                                printf("Enter New Quantity: ");
                                scanf("%u", &newQuantity);
                                clearInputBuffer();
                                if (updateBloodQuantity(bloodGroupId, newQuantity)) {
                                    printf("Blood quantity updated successfully.\n");
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
                                    printf("Invalid blood group.\n");
                                    break;
                                }
                                printf("Enter New Price: ");
                                scanf("%f", &newPrice);
                                clearInputBuffer();
                                if (updateBloodPrice(bloodGroupId, newPrice)) {
                                    printf("Blood price updated successfully.\n");
                                }
                                break;
                            }
                        case 4: {
                                Admin newAdminPassword;
                                printf("Enter New Password: ");
                                getPassword(newAdminPassword.password, sizeof(newAdminPassword.password));
                                if (changeAdminPassword(admin.username, newAdminPassword.password)) {
                                    printf("Admin password updated successfully.\n");
                                }
                                break;
                            }
                        case 5: {
                                Admin newAdmin;
                                printf("Enter New Admin Username: ");
                                fgets(newAdmin.username, sizeof(newAdmin.username), stdin);
                                newAdmin.username[strcspn(newAdmin.username, "\n")] = 0;
                                getPassword(newAdmin.password, sizeof(newAdmin.password));
                                if (addAdmin(newAdmin.username, newAdmin.password)) {
                                    printf("Admin added successfully.\n");
                                }
                                break;
                            }
                        case 6: {
                                Admin delAdmin;
                                printf("Enter Admin Username to Delete: ");
                                fgets(delAdmin.username, sizeof(delAdmin.username), stdin);
                                delAdmin.username[strcspn(delAdmin.username, "\n")] = 0;
                                if (deleteAdmin(delAdmin.username)) {
                                    printf("Admin deleted successfully.\n");
                                }
                                break;
                            }
                        case 7: {
                                Hospital delHospital;
                                printf("Enter Hospital Code to Delete: ");
                                fgets(delHospital.code, sizeof(delHospital.code), stdin);
                                delHospital.code[strcspn(delHospital.code, "\n")] = 0;
                                if (deleteHospital(delHospital.code)) {
                                    printf("Hospital deleted successfully.\n");
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
                            printf("Invalid option. Please try again.\n");
                        }
                    }
                } else {
                    printf("Invalid admin credentials.\n");
                }
                break;
            }
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
        if (choice == 5) {
            break;
        }
    }
    freeAdmin();
    freeHospital();
    freeBloodList();
    freeTransaction();
    return 0;
}
