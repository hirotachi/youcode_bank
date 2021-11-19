//
// Created by hirotachi on 11/19/21.
//

#ifndef YOUCODE_BANK__BANK_H_
#define YOUCODE_BANK__BANK_H_

#define MAX_NATIONAL_ID_LENGTH 25
#define MAX_NAME_LENGTH 255

typedef struct {
  char *nationalID;
  char *firstName;
  char *lastName;
  float amount;
} account;

typedef struct {
  account *accounts;
  size_t accountsSize;
  int accountsCount;
} bank;

void startBank();

void createBankAccount(bank *bankState);

void createMultipleBankAccounts(bank *bankState);

/**
 * finds ank account by national id
 * @param accounts
 * @return -1 for not found or index
 */
int findAccountIndexByID(bank *bankState, char *id);

account createAccount(char *nationalID, char *firstName, char *lastName, float initialAmount);

#endif //YOUCODE_BANK__BANK_H_
