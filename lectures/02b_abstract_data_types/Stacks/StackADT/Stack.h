// Stack.h ... interface to Stack ADT
// Written by John Shepherd, March 2013

#ifndef STACK_H
#define STACK_H

#include "Bool.h"

// client view of Stack objects
typedef struct StackRep *Stack;

// set up empty stack
Stack newStack();

// remove unwanted stack
void dropStack(Stack);

// insert a integer on top of stack
void StackPush(Stack,char);

// remove char from top of stack
char  StackPop(Stack);

// check whether stack is empty
Bool StackIsEmpty(Stack);

#endif
