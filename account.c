//
// Created by hirotachi on 11/19/21.
//

#include <malloc.h>
#include <string.h>
#include "account.h"
#include "bank.h"

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