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
  int sorted; // whether the array is sorted or not
} bank;

void startBank();

void createBankAccount(bank *bankState);

void createMultipleBankAccounts(bank *bankState);

account createAccount(char *nationalID, char *firstName, char *lastName, float initialAmount);

#endif //YOUCODE_BANK__BANK_H_
