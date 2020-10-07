// Stack.c ... array implementation of Stack ADO
// Written by John Shepherd, March 2013

#include <assert.h>
#include "Stack.h"
#include "Bool.h"

#define MAXITEMS 10

static struct {
   char item[MAXITEMS];
   int  top;
} stackObject;

// set up empty stack
void StackInit()
{
   stackObject.top = -1;
}

// insert char on top of stack
void StackPush(char ch)
{
   assert(stackObject.top < MAXITEMS-1);
   stackObject.top++;
   int i = stackObject.top;
   stackObject.item[i] = ch;
}

// remove char from top of stack
char  StackPop()
{
   assert(stackObject.top > -1);
   int i = stackObject.top;
   char ch = stackObject.item[i];
   stackObject.top--;
   return ch;
}

// check whether stack is empty
Bool StackIsEmpty()
{
   return (stackObject.top < 0);
}
