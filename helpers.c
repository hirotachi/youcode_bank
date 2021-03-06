//
// Created by hirotachi on 11/19/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#include <windows.h>

void getStringFromUser(char *var, char *message, int maxLength) {
    printf(message == NULL ? "> " : "%s", message);
    fgets(var, maxLength, stdin);
    var[strcspn(var, "\n")] = '\0'; // fix newline issue
    trimSpaces(var);
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
        if (accounts[j].balance < pivot.balance) {
            i++;
            swap(&accounts[i], &accounts[j]);
        }
    }
    swap(&accounts[i + 1], &accounts[high]);
    return i + 1;
}

void exitProgram(bank *state) {
    cleanMemory(state);
    printf("Thank you for your business!!!\n");
    exit(0);
}

void cleanMemory(bank *state) {
    free(state->accounts);
}

void textColorRed() {
    setColor(12);
}

void textColorReset() {
    setColor(7);
}

void textColorGreen() {
    setColor(10);
}

void setColor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void textColorYellow() {
    setColor(14);
}

void trimSpaces(char *var) {
    size_t length = strlen(var);
    if (length == 0) return;
    size_t start = 0;
    size_t end = length - 1;
    for (int i = 0; i < length; ++i) {
        if (var[start] == ' ')start++;
        if (var[end] == ' ') end--;
    }
    size_t actualLength = end - start + 1;
    char result[actualLength];
    strncpy(result, var + start, actualLength);
    result[actualLength] = '\0';
    strcpy(var, result);
}

void clearTerminal() {
    system("cls");
}



