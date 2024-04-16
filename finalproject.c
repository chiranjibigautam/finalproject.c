// program about banking system that performs basic banking operations such as depositing, withdrawing, and checking account balances for two types of accounts: checking and savings.

#include <stdio.h>

// Structure to represent an account
typedef struct {
    double balance; // Account balance
} Account;

// Structure to represent a bank
typedef struct {
    Account accounts[2]; // Two accounts: 0 for checking, 1 for savings
} Bank;

// Function prototypes
void mainMenu(int *choice);
void depositMoney(Account *account);
void askForAnotherTransaction(int *choice);
void accountMenu(int *typeAcct);
void withdrawMoney(Account *account);
void showBalance(Account *account);
void loadBankData(Bank *bank);
void saveBankData(Bank *bank);

int main() {
    Bank bank;
    loadBankData(&bank); // Load bank data from file

    int choice = 0;

    // Welcome message
    printf("***** Welcome to Legendary Bank *****\n");

    // Main loop
    do {
        printf("** What would you like to do today? **\n");
        mainMenu(&choice);

        switch (choice) {
            case 1: // Deposit
                accountMenu(&choice);
                if (choice == 1 || choice == 2) {
                    depositMoney(&bank.accounts[choice - 1]);
                } else {
                    printf("Invalid account type. Please try again.\n");
                }
                askForAnotherTransaction(&choice);
                break;

            case 2: // Withdrawal
                accountMenu(&choice);
                if (choice == 1 || choice == 2) {
                    withdrawMoney(&bank.accounts[choice - 1]);
                } else {
                    printf("Invalid account type. Please try again.\n");
                }
                askForAnotherTransaction(&choice);
                break;

            case 3: // Check account balance
                accountMenu(&choice);
                if (choice == 1 || choice == 2) {
                    showBalance(&bank.accounts[choice - 1]);
                } else {
                    printf("Invalid account type. Please try again.\n");
                }
                askForAnotherTransaction(&choice);
                break;

            case 4: // Quit
                saveBankData(&bank); // Save bank data to file
                printf("Thank you for banking with us. Have a nice day!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4); // Exit loop if choice is 4

    return 0;
}

// Displays the main menu and sets the user's choice
void mainMenu(int *choice) {
    printf("1 - DEPOSIT\n");
    printf("2 - WITHDRAWAL\n");
    printf("3 - CHECK ACCOUNT BALANCE\n");
    printf("4 - QUIT\n");
    printf("Enter your choice: ");
    if (scanf("%d", choice) != 1) {
        printf("Invalid input. Please try again.\n");
        // Clear the input buffer
        while (getchar() != '\n');
        *choice = -1;
    }
}

// Prompts the user for the amount they want to deposit and updates the selected account
void depositMoney(Account *account) {
    double amount;
    printf("Enter the amount you want to deposit: ");
    if (scanf("%lf", &amount) == 1) {
        account->balance += amount;
        printf("Deposit successful. Your new balance is: %.2lf\n", account->balance);
    } else {
        printf("Invalid input. Please try again.\n");
        // Clear input buffer
        while (getchar() != '\n');
    }
}

// Displays the user’s current account balance for the selected account
void showBalance(Account *account) {
    printf("Your current balance is: %.2lf\n", account->balance);
}

// Prompts the user for the type of account they want to access and sets the chosen account type
void accountMenu(int *typeAcct) {
    printf("Please select an account:\n");
    printf("1 - Checking\n");
    printf("2 - Savings\n");
    printf("Enter your choice: ");
    if (scanf("%d", typeAcct) != 1 || (*typeAcct < 1 || *typeAcct > 2)) {
        printf("Invalid input. Please try again.\n");
        // Clear input buffer
        while (getchar() != '\n');
        *typeAcct = -1;
    }
}

// Prompts the user for the amount they want to withdraw and updates the selected account if funds are dispensed
void withdrawMoney(Account *account) {
    double amount;
    printf("Enter the amount you want to withdraw: ");
    if (scanf("%lf", &amount) == 1) {
        if (amount <= account->balance) {
            account->balance -= amount;
            printf("Withdrawal successful. Your new balance is: %.2lf\n", account->balance);
        } else {
            printf("Insufficient funds.\n");
        }
    } else {
        printf("Invalid input. Please try again.\n");
        // Clear input buffer
        while (getchar() != '\n');
    }
}

// Loads bank data from file
void loadBankData(Bank *bank) {
    FILE *file = fopen("metadata.txt", "rb");
    if (file) {
        fread(bank, sizeof(Bank), 1, file);
        fclose(file);
    } else {
        // File does not exist or cannot be opened; initialize with default values
        bank->accounts[0].balance = 575.00; // Checking account
        bank->accounts[1].balance = 3750.00; // Savings account
    }
}

// Saves bank data to file
void saveBankData(Bank *bank) {
    FILE *file = fopen("metadata.txt", "wb");
    if (file) {
        fwrite(bank, sizeof(Bank), 1, file);
        fclose(file);
    } else {
        printf("Error: Unable to save bank data.\n");
    }
}

// Asks the user if they want another transaction
void askForAnotherTransaction(int *choice) {
    char response;
    printf("Would you like to make another transaction? (Y/N): ");
    scanf(" %c", &response);
    if (response == 'Y' || response == 'y') {
        *choice = 0; // Reset choice to continue
    }
}
