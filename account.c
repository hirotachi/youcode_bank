//
// Created by hirotachi on 11/19/21.
//

#include <malloc.h>
#include <string.h>
#include "account.h"
#include "bank.h"
#include "helpers.h"

account createAccount(char *nationalID, char *firstName, char *lastName, float initialAmount) {
  account result;
  result.amount = initialAmount;

  result.nationalID = malloc(strlen(nationalID) * sizeof(char));
  result.firstName = malloc(strlen(firstName) * sizeof(char));
  result.lastName = malloc(strlen(lastName) * sizeof(char));
  strcpy(result.nationalID, nationalID);
  strcpy(result.firstName, firstName);
  strcpy(result.lastName, lastName);
  return result;
}
int findAccountIndexByID(bank *bankState, char *id) {
  if (bankState->accountsSize != 0) {
    for (int i = 0; i < bankState->accountsCount; ++i) {
      int isSame = strcmp(bankState->accounts[i].nationalID, id);
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

  printf("account with id '%s' doesnt exist.\n", nationalID);
  return -1;
}

void withdraw(bank *state) {
  if (state->accountsCount == 0) {
    printf("There are no accounts yet, create an account first.\n");
    return;
  }

  int accountIndex = getAccountFromUserInput(state);
//  todo add ability to quit operation
  if (accountIndex == -1)return withdraw(state);

  account acc = state->accounts[accountIndex];
  char message[50];
  sprintf(message, "Enter amount to withdraw max is '%.2f$': ", acc.amount);

  float amountToWithdraw;

  int canWithdraw = 0;

  do { // avoid withdrawing more than the account has
    getFloatFromUser(&amountToWithdraw, message);
    if (amountToWithdraw > acc.amount) {
      printf("cannot withdraw more than '%.2f$'.\n", acc.amount);
    } else {
      canWithdraw = 1;
    }
  } while (canWithdraw == 0);

  acc.amount -= amountToWithdraw;
  state->accounts[accountIndex] = acc;

  state->sorted = 0; // mark array as unsorted

  printf("'%.2f$' has been withdrawn successfully from account '%s' of user '%s %s' new amount is '%.2f$'.\n",
         amountToWithdraw,
         acc.nationalID,
         acc.lastName,
         acc.firstName,
         acc.amount
  );
}

void deposit(bank *state) {
  if (state->accountsCount == 0) {
    printf("There are no accounts yet, create an account first.\n");
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
      printf("You're haven't added anything to the account add a positive amount.\n");
    }
  } while (amountToAdd <= 0);
  acc.amount += amountToAdd;
  state->accounts[accountIndex] = acc;

  state->sorted = 0; // mark array as unsorted

  printf("'%.2f$' has been added to account '%s' for '%s %s' successfully new amount is '%.2f$'.\n",
         amountToAdd,
         acc.nationalID,
         acc.lastName,
         acc.firstName,
         acc.amount);
}

void search(bank *state) {
  if (state->accountsCount == 0) {
    printf("There are no accounts yet, create an account first.\n");
    return;
  }
  int accountIndex = getAccountFromUserInput(state);
  if (accountIndex == -1) return;
  account acc = state->accounts[accountIndex];
  printf("This Account belongs to '%s %s' and has '%.2f$'.\n", acc.lastName, acc.firstName, acc.amount);
}

void listAccountsAscending(bank *state) {
  if (state->accountsCount == 0) {
    printf("There are no accounts yet, create an account first.\n");
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
    printf("There are no accounts yet, create an account first.\n");
    return;
  }
  listDescending(state, state->accountsCount, 0);
}

void listAfterAccountsAscending(bank *state) {
  if (state->accountsCount == 0) {
    printf("There are no accounts yet, create an account first.\n");
    return;
  }
  float number;
  getFloatFromUser(&number, "Enter amount to filter by: ");
  if (number <= 0) {
    printf("Enter a positive number.\n");
    return listAfterAccountsAscending(state);
  }
  sortAccounts(state);

  float highestAmount = state->accounts[state->accountsCount - 1].amount;
  if (highestAmount < number) {
    printf("the highest amount available is '%.2f$'\n", highestAmount);
    return;
  }
//   find index where to start
  int index = 0;
  for (int i = 0; i < state->accountsCount; ++i) {
    if (state->accounts[i].amount >= number) {
      index = i;
      break;
    }
  }
  listAscending(state, index, state->accountsCount);
}

void listAscending(bank *state, int start, int end) {
  sortAccounts(state);
  printf("===========================================\n");
  for (int i = start; i < end; ++i) {
    account acc = state->accounts[i];
    printf("%d- ID:'%s' Name:'%s %s' amount:'%.2f$'\n",
           i + 1,
           acc.nationalID,
           acc.lastName,
           acc.firstName,
           acc.amount
    );
  }
  printf("===========================================\n");
}

void listDescending(bank *state, int start, int end) {
  sortAccounts(state);
  printf("===========================================\n");
  for (int i = start - 1; i >= end; --i) {
    account acc = state->accounts[i];
    int order = state->accountsCount - i;

    printf("%d- ID:'%s' Name:'%s %s' amount:'%.2f$'\n",
           order,
           acc.nationalID,
           acc.lastName,
           acc.firstName,
           acc.amount
    );
  }
  printf("===========================================\n");
}






