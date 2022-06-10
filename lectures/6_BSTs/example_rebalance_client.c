// Binary Search Tree ADT Tester ... 

#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"

int myHt(Tree t);

int main(void) {
   Tree myTree = newTree();

   myTree = TreeInsert(myTree, 50);
   myTree = TreeInsert(myTree, 40);
   myTree = TreeInsert(myTree, 80);
   myTree = TreeInsert(myTree, 45);
   myTree = TreeInsert(myTree, 33);
   myTree = TreeInsert(myTree, 70);
   myTree = TreeInsert(myTree, 92);
   myTree = TreeInsert(myTree, 96);
   myTree = TreeInsert(myTree, 99);
   myTree = TreeInsert(myTree, 105);
   myTree = TreeInsert(myTree, 110);
   myTree = TreeInsert(myTree, 120);
   myTree = TreeInsert(myTree, 130);
   myTree = TreeInsert(myTree, 140);
   myTree = TreeInsert(myTree, 150);
 
   int num = TreeNumNodes(myTree);
   printf("num is %d \n", num);

   int ht = myHt(myTree);
   printf("ht is %d \n", ht);
   printf("------------------- -------------------\n"); 
   showTree(myTree);
   printf("------------------- -------------------\n"); 

   myTree = rebalance(myTree, 0);

   printf("------------ After rebalance -------------------\n"); 
   showTree(myTree);
   printf("------------------- -------------------\n"); 

   freeTree(myTree);

 


   return 0;
}

