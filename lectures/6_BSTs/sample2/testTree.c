// Binary Search Tree ADT Tester ... 

#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"

void myPrint(Tree t);
int myCountEven(Tree t);

int main(void) {
   Tree myTree = newTree();

   myTree = TreeInsert(myTree, 50);
   myTree = TreeInsert(myTree, 40);
   myTree = TreeInsert(myTree, 80);
   myTree = TreeInsert(myTree, 45);
   myTree = TreeInsert(myTree, 33);
   myTree = TreeInsert(myTree, 70);
 

   printf("---------------------------- \n");
   showTree(myTree);
   printf("---------------------------- \n");

   myPrint(myTree);
   printf("\n---------------------------- \n");

   int countEven = myCountEven(myTree);

   printf(" count even is %d \n", countEven);
   printf("\n---------------------------- \n");

   freeTree(myTree);

 


   return 0;
}

