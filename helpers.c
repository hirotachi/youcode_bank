//
// Created by hirotachi on 11/19/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

void getStringFromUser(char *var, char *message, int maxLength) {
  printf(message == NULL ? "> " : "%s", message);
  fgets(var, maxLength, stdin);
  var[strcspn(var, "\n")] = '\0'; // fix newline issue
}
void getFloatFromUser(float *var, char *message) {
  char input[25];
  getStringFromUser(input, message, 25);
  *var = strtof(input, NULL);
}
void getIntFromUser(int *var, char *message) {
  char input[25];
  getStringFromUser(input, message, 25);
  *var = strtol(input, NULL, 10);
}


// sorting

void swap(account *account1, account *account2) {
  account temp = *account1;
  *account1 = *account2;
  *account2 = temp;
}

void quickSort(account *accounts, int low, int high) {
  if (low < high) {
    int pi = partition(accounts, low, high);
    quickSort(accounts, low, pi - 1);
    quickSort(accounts, pi + 1, high);
  }
}

int partition(account *accounts, int low, int high) {
  account pivot = accounts[high];
  int i = low - 1;
  for (int j = low; j <= high; ++j) {
    if (accounts[j].amount < pivot.amount) {
      i++;
      swap(&accounts[i], &accounts[j]);
    }
  }
  swap(&accounts[i + 1], &accounts[high]);
  return i + 1;
}


