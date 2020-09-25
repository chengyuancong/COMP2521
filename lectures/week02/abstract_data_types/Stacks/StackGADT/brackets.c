// brackets.c
// Bracket matching using a stack
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

int main(int argc, char *argv[])
{
   char ch;
   Stack brackets;

   brackets = newStack();

   // for each char in stdin
   while ((ch = getchar()) != EOF) {
      if (ch == '(' || ch == '[' || ch == '{') {
         // push opening brackets onto stack
         StackPush(brackets, ch);
      }
      else if (ch == ')' || ch == ']' || ch == '}') {
         if (StackIsEmpty(brackets)) {
            // is there anything on stack to match?
            printf("Unmatched bracket '%c'\n", ch);
            return EXIT_FAILURE;
         }
         else {
            // is it the expected bracket?
            char expected;
            switch (ch) {
            case ')': expected = '('; break;
            case ']': expected = '['; break;
            case '}': expected = '{'; break;
            }
            char c = StackPop(brackets);
            if (c != expected) {
               printf("Mismatch: '%c','%c'\n", c,ch);
               return EXIT_FAILURE;
            }
         }
      }
   }

   // check that everything was matched
   if (!StackIsEmpty(brackets)) {
      char c = StackPop(brackets);
      printf("Unmatched bracket '%c'\n",c);
      return EXIT_FAILURE;
   }
   
   return EXIT_SUCCESS;
}
