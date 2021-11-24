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
            createCommand("average", "Show average of all accounts", showAverage),
            createCommand("search", "Find first account with exact national ID", search),
            createCommand("search q", "List all accounts that include query in national ID", searchByQuery),
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
            createCommand("add bonus", loyaltyDesc, addBonus),
            createCommand("quit", "exit program application", exitProgram),
            createCommand("help", "show this commands list", listMenu),
            createCommand("clear", "clear terminal", clearTerminal),
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

void addBonus(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }

    sortAccounts(state);

    int numberOfAccounts;
    getIntFromUser(&numberOfAccounts, "Enter number of accounts to add loyalty bonus to: ");


    float percentage = LOYALTY_BONUS_PERCENTAGE;
//    add ability to add dynamic percentage
//    char message[100];
//    do {
//        sprintf(message, "Enter percentage to add to top %d accounts: ", numberOfAccounts);
//        getFloatFromUser(&percentage, message);
//        if (percentage < 0.1) {
//            textColorRed();
//            printf("Invalid percentage '%.2f%%', please enter 0.1% and higher.\n", percentage);
//            textColorReset();
//        }
//    } while (percentage < 0.1);


    int count = numberOfAccounts;
    int index = state->accountsCount - 1;
    int changedAccounts = 0;
    while (count > 0 && index >= 0) {
        float amount = state->accounts[index].amount;
        if (amount != state->accounts[index - 1].amount) {
            count--;
        }
        state->accounts[index].amount += (amount / 100 * percentage);
        changedAccounts++;
        index--;
    }

    textColorGreen();
    printf("Added loyalty '%.1f%%' bonus to top %d accounts successfully!!!\n", percentage,
           changedAccounts);
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

void showAverage(bank *state) {
    float total = 0;
    for (int i = 0; i < state->accountsCount; ++i) {
        total += state->accounts[i].amount;
    }
    textColorYellow();
    printf("The average of all %d accounts is '%.2f'", state->accountsCount, total / state->accountsCount);
    textColorReset();
}


