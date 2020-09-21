// Stack.h ... interface to Stack ADO
// Written by John Shepherd, March 2013

#ifndef STACK_H
#define STACK_H

#include "Bool.h"

// set up empty stack
void StackInit();

// insert a char on top of stack
void StackPush(char);

// remove char from top of stack
char StackPop();

// check whether stack is empty
Bool StackIsEmpty();

#endif
