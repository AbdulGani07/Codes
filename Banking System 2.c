#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct BankAccount {
    int accountNumber;
    char accountHolder[100];
    double balance;
};

struct Bank {
    struct BankAccount* accounts[MAX_ACCOUNTS];
    int numAccounts;
};

struct Bank* createBank() {
    struct Bank* bank = (struct Bank*)malloc(sizeof(struct Bank));
    bank->numAccounts = 0;
    return bank;
}

void addAccount(struct Bank* bank, int accountNumber, const char* accountHolder, double initialBalance) {
    if (bank->numAccounts < MAX_ACCOUNTS) {
        struct BankAccount* account = (struct BankAccount*)malloc(sizeof(struct BankAccount));
        account->accountNumber = accountNumber;
        strcpy(account->accountHolder, accountHolder);
        account->balance = initialBalance;
        bank->accounts[bank->numAccounts] = account;
        bank->numAccounts++;
        printf("Account %d created.\n", accountNumber);
    } else {
        printf("Maximum number of accounts reached.\n");
    }
}

struct BankAccount* findAccount(const struct Bank* bank, int accountNumber) {
    for (int i = 0; i < bank->numAccounts; i++) {
        if (bank->accounts[i]->accountNumber == accountNumber) {
            return bank->accounts[i];
        }
    }
    return NULL;
}

void deposit(struct BankAccount* account, double amount) {
    account->balance += amount;
    printf("Deposited %.2f units into account %d. New balance: %.2f\n", amount, account->accountNumber, account->balance);
}

void withdraw(struct BankAccount* account, double amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrawn %.2f units from account %d. New balance: %.2f\n", amount, account->accountNumber, account->balance);
    } else {
        printf("Insufficient funds in account %d\n", account->accountNumber);
    }
}

void checkBalance(const struct BankAccount* account) {
    printf("Account %d, Holder: %s, Balance: %.2f\n", account->accountNumber, account->accountHolder, account->balance);
}

void displayMenu() {
    printf("1. Create Account\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Check Balance\n");
    printf("5. Exit\n");
}

int main() {
    struct Bank* bank = createBank();
    int choice, accountNumber;
    char accountHolder[100];
    double initialBalance, amount;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter account holder name: ");
                scanf("%s", accountHolder);
                printf("Enter initial balance: ");
                scanf("%lf", &initialBalance);
                addAccount(bank, accountNumber, accountHolder, initialBalance);
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                struct BankAccount* depositAccount = findAccount(bank, accountNumber);
                if (depositAccount) {
                    printf("Enter amount to deposit: ");
                    scanf("%lf", &amount);
                    deposit(depositAccount, amount);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                struct BankAccount* withdrawAccount = findAccount(bank, accountNumber);
                if (withdrawAccount) {
                    printf("Enter amount to withdraw: ");
                    scanf("%lf", &amount);
                    withdraw(withdrawAccount, amount);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                struct BankAccount* checkAccount = findAccount(bank, accountNumber);
                if (checkAccount) {
                    checkBalance(checkAccount);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 5);

    // Free memory for bank accounts
    for (int i = 0; i < bank->numAccounts; i++) {
        free(bank->accounts[i]);
    }
    free(bank);

    return 0;
}

