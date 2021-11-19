//
// Created by hirotachi on 11/19/21.
//

#ifndef YOUCODE_BANK__ACCOUNT_H_
#define YOUCODE_BANK__ACCOUNT_H_
#include "bank.h"

void withdraw(bank *state);
void deposit(bank *bankState);

/**
 * finds ank account by national id
 * @param accounts
 * @return -1 for not found or index
 */
int findAccountIndexByID(bank *bankState, char *id);

/**
 * find account by id entered by user
 * @param bankState
 * @return
 */
int getAccountFromUserInput(bank *bankState);

void search(bank *state);
void listAccountsAscending(bank *state);
void listAccountsDescending(bank *state);
void sortAccounts(bank *state);

#endif //YOUCODE_BANK__ACCOUNT_H_
