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

  do {
    getFloatFromUser(&amountToWithdraw, message);
    if (amountToWithdraw > acc.amount) {
      printf("cannot withdraw more than '%.2f$'.\n", acc.amount);
    } else {
      canWithdraw = 1;
    }
  } while (canWithdraw == 0);
  acc.amount -= amountToWithdraw;
  state->accounts[accountIndex] = acc;
  printf("'%.2f$' has been withdrawn successfully from account '%s' of user '%s %s' new amount is '%.2f$'.\n",
         amountToWithdraw,
         acc.nationalID,
         acc.lastName,
         acc.firstName,
         acc.amount
  );
}

void deposit(bank *bankState) {

}