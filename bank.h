//
// Created by hirotachi on 11/19/21.
//

#ifndef YOUCODE_BANK__BANK_H_
#define YOUCODE_BANK__BANK_H_

#define MAX_NATIONAL_ID_LENGTH 25
#define MAX_NAME_LENGTH 255
#define LOYALTY_BONUS_PERCENTAGE 1.3

typedef struct {
    char nationalID[MAX_NATIONAL_ID_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    float balance;
} account;

typedef struct {
    account *accounts;
    size_t accountsSize;
    int accountsCount;
    int sorted; // whether the array is sorted or not
} bank;

void startBank();

void createBankAccount(bank *bankState);

void removeBankAccount(bank *state);

void createMultipleBankAccounts(bank *bankState);

/**
 * adds loyalty bonus to top 3 accounts with the most balance
 * @param state
 */
void addBonus(bank *state);

void showAverage(bank *state);

#endif //YOUCODE_BANK__BANK_H_
