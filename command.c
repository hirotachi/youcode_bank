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
    int nameSize = strlen(name) + 1;
    int descriptionSize = strlen(description) + 1;
    result.name = malloc(nameSize * sizeof(char));
    if (result.name == NULL) {
        printf("failed to allocate memory for command name '%s'\n", name);
    }
    result.description = malloc(descriptionSize * sizeof(char));
    if (result.name == NULL) {
        printf("failed to allocate memory for command description '%s'\n", name);
    }

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
        printf("\n");
    }
    printf("Please Enter a command from the list ('help' to show list).\n");
    char enteredCommand[MAX_COMMAND_LENGTH];
    getStringFromUser(enteredCommand, NULL, MAX_COMMAND_LENGTH);
    printf("\n");

    int isCommandFound = 0; // to render error in case command is not found
    for (int i = 0; i < length; ++i) {
        command com = commands[i];
        int isSame = stricmp(enteredCommand, com.name);
        if (isSame == 0) {
            isCommandFound = 1;
            com.handler(bankState);
            showAndHandleCommands(length, commands, bankState, 0);
            break;
        }
    }

    if (isCommandFound == 0) {
        textColorRed();
        printf("Unknown command '%s', please enter a command from the list.\n", enteredCommand);
        textColorReset();
        showAndHandleCommands(length, commands, bankState, 0);
    }
}
