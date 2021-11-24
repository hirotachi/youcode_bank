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

/**
 * find one account equal to entered ID
 * @param state
 */
void search(bank *state);

/**
 * print all accounts that include substring of ID
 * @param state
 */
void searchByQuery(bank *state);

void listAccountsAscending(bank *state);

void listAccountsDescending(bank *state);

void listAfterAccountsDescending(bank *state);

void listAfterAccountsAscending(bank *state);

void sortAccounts(bank *state);

account createAccount(char *nationalID, char *firstName, char *lastName, float initialBalance);

void listAscending(bank *state, int start, int end);

void listDescending(bank *state, int start, int end);

void printAccount(account acc, int order);

int findAfterAmountIndex(bank *state);

#endif //YOUCODE_BANK__ACCOUNT_H_
