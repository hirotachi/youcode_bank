//
// Created by hirotachi on 11/19/21.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "bank.h"
#include "command.h"
#include "helpers.h"
#include "account.h"

void initializeBankState(bank *b) {
    int initialSize = 10;
    b->accountsSize = initialSize;
    b->accountsCount = 0;
    b->sorted = 0;
    b->accounts = malloc(initialSize * sizeof(account));
}

void listMenu(bank *b) {
    char loyaltyDesc[50];
    sprintf(loyaltyDesc, "Adds %.1f%% loyalty bonus to top n accounts", LOYALTY_BONUS_PERCENTAGE);

    command commands[] = {
            createCommand("create account", "Create a bank account", createBankAccount),
            createCommand("remove account", "Remove a bank account", removeBankAccount),
            createCommand("create accounts", "Create multiple accounts", createMultipleBankAccounts),
            createCommand("withdraw", "Withdraw from an account", withdraw),
            createCommand("deposit", "Deposit money to an account", deposit),
            createCommand("search", "Search for a bank account by national ID", search),
            createCommand("list a", "List bank accounts by ascending order", listAccountsAscending),
            createCommand("list d", "List bank accounts by descending order", listAccountsDescending),
            createCommand(
                    "list aa",
                    "List bank accounts by ascending order after a certain amount",
                    listAfterAccountsAscending
            ),
            createCommand(
                    "list ad",
                    "List bank accounts by descending order after a certain amount",
                    listAfterAccountsDescending
            ),
            createCommand("add bonus", loyaltyDesc, addLoyaltyBonus),
            createCommand("quit", "exit program application", exitProgram),
            createCommand("help", "show this commands list", listMenu),
    };

    size_t commandsLength = sizeof(commands) / sizeof(commands[0]);
    showAndHandleCommands(commandsLength, commands, b, 1);
}

void startBank() {
    bank bankState;
    initializeBankState(&bankState);
    listMenu(&bankState);
}

void createBankAccount(bank *b) {
    char nationalID[MAX_NATIONAL_ID_LENGTH];
    getStringFromUser(nationalID, "Please Enter national ID: ", MAX_NATIONAL_ID_LENGTH);

    int index = findAccountIndexByID(b, nationalID);
    if (index != -1) {
        textColorRed();
        printf("account with ID '%s' already exists.\n", nationalID);
        textColorReset();
        return createBankAccount(b);
    }
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
    float initialAmount = 0;
    getStringFromUser(firstName, "Please Enter first name: ", MAX_NAME_LENGTH);
    getStringFromUser(lastName, "Please Enter last name: ", MAX_NAME_LENGTH);
    getFloatFromUser(&initialAmount, "Please Enter initial amount for this account: ");

    if (b->accountsSize == b->accountsCount) {
        b->accountsSize += 10;
        account *newArray = realloc(b->accounts, b->accountsSize * sizeof(account));
        if (newArray == NULL) { // failing to increase space on memory
            printf("Failed to create space for new bank account.\n");
            return listMenu(b);
        }
    }
    account newAccount = createAccount(nationalID, firstName, lastName, initialAmount);
    b->accounts[b->accountsCount] = newAccount;
    b->accountsCount++;
    b->sorted = 0;
    textColorGreen();
    printf("Account with ID '%s' for '%s %s' and amount of '%.2f$' has been created successfully!!\n",
           newAccount.nationalID,
           newAccount.lastName,
           newAccount.firstName,
           newAccount.amount);
    textColorReset();
}

void createMultipleBankAccounts(bank *bankState) {
    int count;
    getIntFromUser(&count, "Enter number of accounts to create: ");
    for (int i = 0; i < count; ++i) {
        printf("account (%d) - ", i + 1);
        createBankAccount(bankState);
    }
}

void addLoyaltyBonus(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }

    sortAccounts(state);

    int numberOfAccounts;
    getIntFromUser(&numberOfAccounts, "Enter number of accounts to add loyalty bonus to: ");
    for (int i = state->accountsCount - 1; i >= 0; --i) {
        int isLoyal = state->accountsCount - i <= numberOfAccounts ? 1 : 0;
        if (isLoyal == 1) {
            float amount = state->accounts[i].amount;
            state->accounts[i].amount = amount + (amount / 100 * LOYALTY_BONUS_PERCENTAGE);
        }
    }
    textColorGreen();
    printf("Added loyalty '%.1f%%' bonus to top %d accounts successfully!!!\n", LOYALTY_BONUS_PERCENTAGE,
           numberOfAccounts);
    textColorReset();
}

void removeBankAccount(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }
    int accountIndex = getAccountFromUserInput(state);
    if (accountIndex == -1) return;

//   filter account from array
    account *accounts = malloc(state->accountsSize * sizeof(account));
    int index = 0;
    for (int i = 0; i < state->accountsCount; ++i) {
        if (accountIndex == i) continue;
        accounts[index] = state->accounts[i];
        index++;
    }
    state->accountsCount = index;
    account acc = state->accounts[accountIndex];

    textColorGreen();
    printf("Account with ID '%s' for user '%s %s' has been removed successfully!\n",
           acc.nationalID,
           acc.lastName,
           acc.firstName);
    textColorReset();
    free(state->accounts);
    state->accounts = NULL;
    state->accounts = accounts;
}


