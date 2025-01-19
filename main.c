#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include "include/admin_manager.h"
#include "include/hospital_manager.h"
#include "include/blood_manager.h"
#include "include/transaction_manager.h"

void displayUserMenu();

void displayAdminMenu();

void getPassword(char* password, size_t size);

int main() {
    loadBloodGroups();
    loadHospitals();
    loadAdminCredentials();

    int choice;
    int isAdmin = 0;

    while (1) {
        displayUserMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
                if (!isBloodAvailable(BUY)) {
                    printf("No blood available for buy.\n");
                    break;
                }
                TransactionType type = BUY;
                char name[50];
                char bloodGroup[BLOOD_GROUP_NAME_LENGTH];
                uint32_t quantity;
                printf("Enter Entity Name (Hospital Code): ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                if (!validateHospitalCode(name)) {
                    printf("Invalid hospital code: %s\n", name);
                    break;
                }

                displayBloodStocks();
                printf("Enter Blood Group: ");
                fgets(bloodGroup, sizeof(bloodGroup), stdin);
                bloodGroup[strcspn(bloodGroup, "\n")] = 0;
                if (!isValidBloodGroup(bloodGroup)) {
                    printf("Invalid blood group: %s\n", bloodGroup);
                    break;
                }
                if (!isBloodGroupAvailable(bloodGroup)) {
                    printf("No stock available for blood group: %s\n", bloodGroup);
                    break;
                }
                printf("Enter Quantity: ");
                scanf("%u", &quantity);
                if (addTransaction(type, name, bloodGroup, quantity)) {
                    printf("Transaction added successfully.\n");
                } else {
                    printf("Failed to add transaction.\n");
                }
                break;
            }
        case 2: {
                if (!isBloodAvailable(SELL)) {
                    printf("No blood available for sell.\n");
                    break;
                }
                TransactionType type = SELL;
                char donorName[50];
                char bloodGroup[BLOOD_GROUP_NAME_LENGTH];
                uint32_t quantity;

                printf("Enter Donor Name: ");
                fgets(donorName, sizeof(donorName), stdin);
                donorName[strcspn(donorName, "\n")] = 0;

                displayBloodStocks();
                printf("Enter Blood Group: ");
                fgets(bloodGroup, sizeof(bloodGroup), stdin);
                bloodGroup[strcspn(bloodGroup, "\n")] = 0;

                if (!isValidBloodGroup(bloodGroup)) {
                    printf("Invalid blood group: %s\n", bloodGroup);
                    break;
                }

                printf("Enter Quantity: ");
                scanf("%u", &quantity);

                if (addTransaction(type, donorName, bloodGroup, quantity)) {
                    printf("Transaction added successfully.\n");
                } else {
                    printf("Failed to add transaction.\n");
                }
                break;
            }
        case 3:
            displayBloodStocks();
            break;
        case 4: {

                char username[20], password[20];
                printf("Enter Admin Username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;
                getPassword(password, sizeof(password));

                if (validateAdmin(username, password)) {
                    isAdmin = 1;
                    printf("Admin logged in successfully.\n");

                    while (isAdmin) {
                        displayAdminMenu();
                        scanf("%d", &choice);
                        getchar();

                        switch (choice) {
                        case 1: {
                                char name[50], location[50];
                                printf("Enter Hospital Name: ");
                                fgets(name, sizeof(name), stdin);
                                name[strcspn(name, "\n")] = 0;
                                printf("Enter Hospital Location: ");
                                fgets(location, sizeof(location), stdin);
                                location[strcspn(location, "\n")] = 0;
                                if (addHospital(name, location)) {
                                    printf("Hospital added successfully.\n");
                                } else {
                                    printf("Failed to add hospital.\n");
                                }
                                break;
                            }
                        case 2: {
                                displayBloodGroups();
                                char bloodGroupInput[BLOOD_GROUP_NAME_LENGTH];
                                uint32_t newQuantity;
                                printf("Enter Blood Group: ");
                                fgets(bloodGroupInput, sizeof(bloodGroupInput), stdin);
                                bloodGroupInput[strcspn(bloodGroupInput, "\n")] = 0;
                                if (!isValidBloodGroup(bloodGroupInput)) {
                                    printf("Invalid blood group: %s\n", bloodGroupInput);
                                    break;
                                }
                                if (!isBloodAvailable(SELL)) {
                                    float newPrice;
                                    printf("Price for %s is not set.\n", bloodGroupInput);
                                    printf("Enter New Price: ");
                                    scanf("%f", &newPrice);
                                    if (updateBloodPrice(bloodGroupInput, newPrice)) {
                                        printf("Blood price updated successfully.\n");
                                    } else {
                                        printf("Failed to update blood price.\n");
                                        break;
                                    }
                                }
                                printf("Enter New Quantity: ");
                                scanf("%u", &newQuantity);
                                if (updateBloodQuantity(bloodGroupInput, newQuantity)) {
                                    printf("Blood quantity updated successfully.\n");
                                } else {
                                    printf("Failed to update blood quantity.\n");
                                }
                                break;
                            }
                        case 3: {
                                displayBloodGroups();
                                char bloodGroupInput[BLOOD_GROUP_NAME_LENGTH];
                                float newPrice;
                                printf("Enter Blood Group: ");
                                fgets(bloodGroupInput, sizeof(bloodGroupInput), stdin);
                                bloodGroupInput[strcspn(bloodGroupInput, "\n")] = 0;
                                if (!isValidBloodGroup(bloodGroupInput)) {
                                    printf("Invalid blood group: %s\n", bloodGroupInput);
                                    break;
                                }
                                printf("Enter New Price: ");
                                scanf("%f", &newPrice);
                                if (updateBloodPrice(bloodGroupInput, newPrice)) {
                                    printf("Blood price updated successfully.\n");
                                } else {
                                    printf("Failed to update blood price.\n");
                                }
                                break;
                            }
                        case 4: {
                                char newPassword[20];
                                printf("Enter New Password: ");
                                fgets(newPassword, sizeof(newPassword), stdin);
                                newPassword[strcspn(newPassword, "\n")] = 0;
                                changeAdminPassword(username, newPassword);
                                break;
                            }
                        case 5: {
                                char newUsername[20], newPassword[20];
                                printf("Enter New Admin Username: ");
                                fgets(newUsername, sizeof(newUsername), stdin);
                                newUsername[strcspn(newUsername, "\n")] = 0;
                                getPassword(newPassword, sizeof(newPassword));
                                addAdmin(newUsername, newPassword);
                                break;
                            }
                        case 6: {
                                char delUsername[20];
                                printf("Enter Admin Username to Delete: ");
                                fgets(delUsername, sizeof(delUsername), stdin);
                                delUsername[strcspn(delUsername, "\n")] = 0;
                                deleteAdmin(delUsername);
                                break;
                            }
                        case 7: {
                                displayAdmin();
                                break;
                            }
                        case 8: {
                                displayHospitals();
                                break;
                            }
                        case 9: {
                                displayBloodStocks();
                                break;
                            }
                        case 10: {
                                displayTransactions();
                                break;
                            }
                        case 11:
                            printf("Exiting admin panel...\n");
                            isAdmin = 0;
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
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

void displayUserMenu() {
    printf("\n--- CrimsonCare Blood Bank Management System (User) ---\n");
    printf("1. Buy Blood\n");
    printf("2. Sell Blood\n");
    printf("3. Display Blood Stocks\n");
    printf("4. Admin Panel\n");
    printf("5. Exit\n");
    printf("Select an option: ");
}

void displayAdminMenu() {
    printf("\n--- CrimsonCare Blood Bank Management System (Admin) ---\n");
    printf("1. Add Hospital\n");
    printf("2. Update Blood Quantity\n");
    printf("3. Update Blood Price\n");
    printf("4. Change Admin Password\n");
    printf("5. Add Admin\n");
    printf("6. Delete Admin\n");
    printf("7. Display Admins\n");
    printf("8. Display Hospitals\n");
    printf("9. Display Blood Stocks\n");
    printf("10. Display Transactions\n");
    printf("11. Exit\n");
    printf("Select an option: ");
}

void getPassword(char* password, size_t size) {
#ifdef _WIN32

    printf("Enter Password: ");
    size_t i = 0;
    char ch;
    while (i < size - 1) {

        ch = getch();

        if (ch == '\r') {

            break;
        } else if (ch == '\b') {

            if (i > 0) {
                i--;
                printf("\b \b");

            }
        } else {
            password[i++] = ch;
            printf("*");

        }
    }
    password[i] = '\0';

    printf("\n");
#else

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    newt.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Enter Password: ");
    fgets(password, size);
    password[strcspn(password, "\n")] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    printf("\n");
#endif
}
