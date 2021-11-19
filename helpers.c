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


