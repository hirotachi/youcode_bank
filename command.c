//
// Created by hirotachi on 11/19/21.
//

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "command.h"
#include "helpers.h"
#include "bank.h"

command createCommand(char *name, char *description, void (*handler)()) {
  command result;
  size_t nameSize = strlen(name);
  size_t descriptionSize = strlen(description);
  result.name = malloc(nameSize * sizeof(char));
  result.description = malloc(descriptionSize * sizeof(char));

  strcpy(result.name, name);
  strcpy(result.description, description);
  result.handler = handler;
  return result;
}

void showAndHandleCommands(size_t length, command commands[], bank *bankState, int showList) {
  printf("\n");
  if (showList != 0) {
    for (int i = 0; i < length; ++i) {
      command com = commands[i];
      printf("%s - %s.\n", com.name, com.description);
    }
    printf("Please Enter a command from the list.\n");
  }
  char enteredCommand[MAX_COMMAND_LENGTH];
  getInputFromUser(enteredCommand, NULL, MAX_COMMAND_LENGTH);

  int isCommandFound = 0; // to render error in case command is not found
  for (int i = 0; i < length; ++i) {
    command com = commands[i];
    int isSame = strcmp(enteredCommand, com.name);
    if (isSame == 0) {
      isCommandFound = 1;
      com.handler(bankState);
      showAndHandleCommands(length, commands, bankState, 1);
      break;
    }
  }

  if (isCommandFound == 0) {
    printf("Unknown command '%s', please enter a command from the list.\n", enteredCommand);
    showAndHandleCommands(length, commands, bankState, 0);
  }
}
