#include <stdio.h>
#include "bank.h"
//
// Created by hirotachi on 11/19/21.
//
int main() {
  printf("welcome to the banking program\n");
  startBank();
  //   welcome message
// list menu of operations
//1- create bank account -> get cin check if cin already exists -> if yes -> print error that it exists and rerun last step
//                                                                 else -> get name and amount and save to state
//2- create multiple bank accounts -> ask for number of accounts -> for each cin entered check if it exists -> error if it exists and retry if not create the bank account
//3- withdraw -> ask for CIN -> if it exists ask for amount -> if amount is more than bank account amount -> error and retry asking for amount
//                                                       -> else remove amount from bank account and show message that account has been updated and has amount left
//4-deposit -> ask for cin -> if exists ask for amount -> and add to amount with feedback
//5- list ascending -> list bank accounts by ascending order
//6- list descending -> list bank accounts by descending order
//7- search -> enter CIN
//8- add loyalty bonus
//9- quit program
}
