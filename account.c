//
// Created by hirotachi on 11/19/21.
//

#include <string.h>
#include <stdio.h>
#include "account.h"
#include "helpers.h"

account createAccount(char *nationalID, char *firstName, char *lastName, float initialBalance) {
    account result;
    result.balance = initialBalance;

    strcpy(result.nationalID, nationalID);
    strcpy(result.firstName, firstName);
    strcpy(result.lastName, lastName);
    return result;
}

int findAccountIndexByID(bank *bankState, char *id) {
    if (bankState->accountsSize != 0) {
        for (int i = 0; i < bankState->accountsCount; ++i) {
            int isSame = stricmp(bankState->accounts[i].nationalID, id);
            if (isSame == 0) {
                return i;
            }
        }
    }
    return -1;
}

int getAccountFromUserInput(bank *b) {
    char nationalID[MAX_NATIONAL_ID_LENGTH];
    getStringFromUser(nationalID, "Please Enter account's national ID: ", MAX_NATIONAL_ID_LENGTH);
    int accountIndex = findAccountIndexByID(b, nationalID);
    if (accountIndex != -1) return accountIndex;

    textColorRed();
    printf("account with id '%s' doesnt exist.\n", nationalID);
    textColorReset();
    return -1;
}

void withdraw(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }

    int accountIndex = getAccountFromUserInput(state);
//  todo add ability to quit operation
    if (accountIndex == -1)return withdraw(state);

    account acc = state->accounts[accountIndex];
    char message[50];
    sprintf(message, "Enter an amount to withdraw max is '%.2f$': ", acc.balance);

    float amountToWithdraw;

    int canWithdraw = 0;

    do { // avoid withdrawing more than the account has
        getFloatFromUser(&amountToWithdraw, message);
        if (amountToWithdraw > acc.balance) {
            textColorRed();
            printf("cannot withdraw more than '%.2f$'.\n", acc.balance);
            textColorReset();
        } else {
            canWithdraw = 1;
        }
    } while (canWithdraw == 0);

    acc.balance -= amountToWithdraw;
    state->accounts[accountIndex] = acc;

    state->sorted = 0; // mark array as unsorted

    textColorGreen();
    printf("'%.2f$' has been withdrawn successfully from account '%s' of user '%s %s' new balance is '%.2f$'.\n",
           amountToWithdraw,
           acc.nationalID,
           acc.lastName,
           acc.firstName,
           acc.balance
    );
    textColorReset();
}

void deposit(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }

    int accountIndex = getAccountFromUserInput(state);
//  todo add ability to quit operation
    if (accountIndex == -1)return withdraw(state);

    account acc = state->accounts[accountIndex];
    float amountToAdd;
    do { // in case the user enters 0 or less
        getFloatFromUser(&amountToAdd, "Enter Amount to deposit: ");
        if (amountToAdd <= 0) {
            textColorRed();
            printf("You haven't added anything to the account add a positive number.\n");
            textColorReset();
        }
    } while (amountToAdd <= 0);
    acc.balance += amountToAdd;
    state->accounts[accountIndex] = acc;

    state->sorted = 0; // mark array as unsorted

    textColorGreen();
    printf("'%.2f$' has been added to account '%s' for '%s %s' successfully new balance is '%.2f$'.\n",
           amountToAdd,
           acc.nationalID,
           acc.lastName,
           acc.firstName,
           acc.balance);
    textColorReset();
}

void listAccountsAscending(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }
    listAscending(state, 0, state->accountsCount);
}


void sortAccounts(bank *state) {
    if (state->accountsCount <= 1 || state->sorted == 1) return;
    // only sort when there is more than one account and if the array is not sorted already
    quickSort(state->accounts, 0, state->accountsCount - 1);
    state->sorted = 1;
}

void listAccountsDescending(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }
    listDescending(state, state->accountsCount, 0);
}

void listAfterAccountsAscending(bank *state) {
    int accountIndex = findAfterAmountIndex(state);
    if (accountIndex == -1)return;
    listAscending(state, accountIndex, state->accountsCount);
}

void listAfterAccountsDescending(bank *state) {
    int accountIndex = findAfterAmountIndex(state);
    if (accountIndex == -1)return;
    listDescending(state, state->accountsCount, accountIndex);
}

void listAscending(bank *state, int start, int end) {
    sortAccounts(state);
    printf("List of %d accounts: \n", end - start);
    printf("===========================================\n");
    int order = 1;
    for (int i = start; i < end; ++i) {
        printAccount(state->accounts[i], order);
        order++;
    }
    printf("===========================================\n");
}

void listDescending(bank *state, int start, int end) {
    sortAccounts(state);
    printf("List of %d accounts: \n", start - end);
    printf("===========================================\n");
    int order = 1;
    for (int i = start - 1; i >= end; --i) {
        printAccount(state->accounts[i], order);
        order++;
    }
    printf("===========================================\n");
}

void printAccount(account acc, int order) {
    printf("%d - ID:'%s' Name:'%s %s' Balance:'%.2f$'\n",
           order,
           acc.nationalID,
           acc.lastName,
           acc.firstName,
           acc.balance
    );
}

int findAfterAmountIndex(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return -1;
    }
    float amount;
    getFloatFromUser(&amount, "Enter a balance to list after: ");
    if (amount <= 0) {
        textColorRed();
        printf("Enter a positive number.\n");
        textColorReset();
        return findAfterAmountIndex(state);
    }
    sortAccounts(state);


    float highestAmount = state->accounts[state->accountsCount - 1].balance;
    if (highestAmount < amount) {
        textColorRed();
        printf("the highest balance available is '%.2f$'.\n", highestAmount);
        textColorReset();
        return -1;
    }

    int index = 0;
    for (int i = 0; i < state->accountsCount; ++i) {
        if (state->accounts[i].balance >= amount) {
            index = i;
            break;
        }
    }
    return index;
}

void search(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }
    int accountIndex = getAccountFromUserInput(state);
    if (accountIndex == -1) return;
    account acc = state->accounts[accountIndex];
    textColorYellow();
    printf("This Account belongs to '%s %s' and has a balance of '%.2f$'.\n", acc.lastName, acc.firstName, acc.balance);
    textColorReset();
}

void searchByQuery(bank *state) {
    if (state->accountsCount == 0) {
        textColorRed();
        printf("There are no accounts yet, create an account first.\n");
        textColorReset();
        return;
    }
    int maxLength = 25;
    char query[maxLength];
    getStringFromUser(query, "Please Enter text to search for: ", maxLength);
    if (strlen(query) == 0) {
        textColorRed();
        printf("empty query provided, aborting search.\n");
        textColorReset();
        return;
    }

    int foundCount = 0;
    for (int i = 0; i < state->accountsCount; ++i) {
        account acc = state->accounts[i];
        if (strstr(acc.nationalID, query) != NULL) {
            foundCount++;
        }
    }
    if (foundCount == 0) {
        textColorRed();
        printf("'%s' has 0 matches in the database.\n", query);
        textColorReset();
        return;
    }

    sortAccounts(state);
    printf("Search result for '%s' %d matches: \n", query, foundCount);
    printf("============================================\n");
    int order = 1;
    for (int i = state->accountsCount - 1; i >= 0; --i) {
        account acc = state->accounts[i];
        if (strstr(acc.nationalID, query) != NULL) {
            printAccount(acc, order);
            order++;
        }
    }
    printf("============================================\n");
}






