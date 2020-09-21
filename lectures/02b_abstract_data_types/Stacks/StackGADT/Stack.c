// Stack.c
// array implementation of Stack DT
// Written by John Shpherd, March 2013

#include <stdlib.h>
#include <assert.h>
#include "Item.h"
#include "Stack.h"
#include "Bool.h"

#define MAXITEMS 10

typedef struct StackRep {
   Item item[MAXITEMS];
   int  top;
} StackRep;

// set up empty stack
Stack newStack()
{
   Stack s;
   s = malloc(sizeof(StackRep));
   assert(s != NULL);
   s->top = -1;
   return s;
}

// remove unwanted stack
void dropStack(Stack s)
{
   assert(s != NULL);
   free(s);
}

// insert char on top of stack
void StackPush(Stack s, Item it)
{
   assert(s->top < MAXITEMS-1);
   s->top++;
   int i = s->top;
   s->item[i] = copy(it);
}

// remove char from top of stack
char  StackPop(Stack s)
{
   assert(s->top > -1);
   int i = s->top;
   Item it = copy(s->item[i]);
   s->top--;
   return it;
}

// check whether stack is empty
Bool StackIsEmpty(Stack s)
{
   return (s->top < 0);
}
