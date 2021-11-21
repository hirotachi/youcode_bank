//
// Created by hirotachi on 11/19/21.
//

#include "account.h"

#ifndef YOUCODE_BANK__HELPERS_H_
#define YOUCODE_BANK__HELPERS_H_

void getStringFromUser(char *var, char *message, int maxLength);

void getFloatFromUser(float *var, char *message);

void getIntFromUser(int *var, char *message);

int partition(account accounts[], int low, int high);

void quickSort(account accounts[], int low, int high);

void swap(account *account1, account *account2);

void cleanMemory(bank *state);

void exitProgram(bank *state);

void textColorRed();

void textColorYellow();

void textColorReset();

void textColorGreen();


/**
 * change output text color
 * @param colorNum
 */
void setColor(int colorNum);

#endif //YOUCODE_BANK__HELPERS_H_
