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
  b->accounts = malloc(initialSize * sizeof(account));
}
void listMenu(bank *b) {
  command commands[] = {
      createCommand("create account", "Create a bank account", createBankAccount),
      createCommand("create accounts", "Create multiple accounts", createMultipleBankAccounts),
      createCommand("withdraw", "Withdraw from an account", withdraw),
      createCommand("deposit", "Deposit money to an account", deposit),
  };
  size_t commandsLength = sizeof(commands) / sizeof(commands[0]);
  showAndHandleCommands(commandsLength, commands, b, 1);
}

void startBank() {
  bank bankState;
  initializeBankState(&bankState);
  listMenu(&bankState);

  printf("Program has started");

}

void createBankAccount(bank *b) {
  char nationalID[MAX_NATIONAL_ID_LENGTH];
  getStringFromUser(nationalID, "Please Enter national ID: ", MAX_NATIONAL_ID_LENGTH);

  int index = findAccountIndexByID(b, nationalID);
  if (index != -1) {
    printf("account with ID '%s' already exists.\n", nationalID);
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
  printf("Account with ID '%s' for '%s %s' and amount of '%.2f$' has been created successfully!!\n",
         newAccount.nationalID,
         newAccount.lastName,
         newAccount.firstName,
         newAccount.amount);
}

void createMultipleBankAccounts(bank *bankState) {
  int count;
  getIntFromUser(&count, "Enter number of accounts to create: ");
  for (int i = 0; i < count; ++i) {
    printf("account (%d) - ", i + 1);
    createBankAccount(bankState);
  }
}


