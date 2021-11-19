//
// Created by hirotachi on 11/19/21.
//

#ifndef YOUCODE_BANK__COMMAND_H_
#define YOUCODE_BANK__COMMAND_H_

#define MAX_COMMAND_LENGTH 255

typedef struct {
  char *name;
  char *description;
  void (*handler)();
} command;

/**
 * create and return a command struct filled
 * @param name
 * @param description
 * @param handler
 * @return
 */
command createCommand(char name[], char description[], void(*handler)());

/**
 * list commands and wait for user to enter input to be handled by the right command
 * @param commands
 */
void showAndHandleCommands(command commands[]);

#endif //YOUCODE_BANK__COMMAND_H_
