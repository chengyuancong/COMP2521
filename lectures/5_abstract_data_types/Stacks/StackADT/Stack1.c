// Stack.c
// array implementation of Stack ADT
// Written by John Shpherd, March 2013

#include <stdlib.h>
#include <assert.h>
#include "Stack.h"
#include "Bool.h"

#define MAXITEMS 10

typedef struct StackRep {
   char *item;
   int  size;
   int  top;
} StackRep;

// set up empty stack
Stack newStack(int N)
{
   Stack s;
   s = malloc(sizeof(StackRep));
   assert(s != NULL);
   s->item = malloc(N * (sizeof char));
   assert(s->item != NULL);
   s->size = N;
   s->top = -1;
   return s;
}

// remove unwanted stack
void dropStack(Stack s)
{
   assert(s != NULL);
   free(s->item);
   free(s);
}

// insert char on top of stack
void StackPush(Stack s, char ch)
{
   if (s->top == MAXITEMS-1) {
      // fix array size
      
   }
   s->top++;
   int i = s->top;
   s->item[i] = ch;
}

// remove char from top of stack
char  StackPop(Stack s)
{
   assert(s->top > -1);
   int i = s->top;
   char ch = s->item[i];
   s->top--;
   return ch;
}

// check whether stack is empty
Bool StackIsEmpty(Stack s)
{
   return (s->top < 0);
}
