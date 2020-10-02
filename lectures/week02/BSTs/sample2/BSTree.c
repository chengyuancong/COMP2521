// Binary Search Tree ADT implementation ... 

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "BSTree.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   int  data;
   Tree left, right;
} Node;


// make a new node containing data
Tree newNode(Item data) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   new->data = data;
   new->left = new->right = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

// compute height of Tree
int TreeHeight(Tree t) {

   // not yet implemented

   return -1;
}

// count #nodes in Tree
int TreeNumNodes(Tree t) {
   if (t == NULL)
      return 0;
   else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (it < t->data )
      return TreeSearch( t->left, it);
   else if (it > data(t))
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
   if (t == NULL)
      t = newNode(it);

   else if (it < data(t))
      t->left = TreeInsert(t->left, it);

   else if (it > data(t))
      right(t) = TreeInsert(right(t), it);


   return t;
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t1;
   else if (t2 == NULL)
      return t2;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	 parent = curr;
	 curr = left(curr);
      }
      if (parent != NULL) {
	 left(parent) = right(curr);  // unlink min element from parent
	 right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
   if (t != NULL) {
      if (it < data(t))
	 left(t) = TreeDelete(left(t), it);
      else if (it > data(t))
	 right(t) = TreeDelete(right(t), it);
      else {
	 Tree new;
	 if (left(t) == NULL && right(t) == NULL) 
	    new = NULL;
	 else if (left(t) == NULL)    // if only right subtree, make it the new root
	    new = right(t);
	 else if (right(t) == NULL)   // if only left subtree, make it the new root
	    new = left(t);
	 else                         // left(t) != NULL and right(t) != NULL
	    new = joinTrees(left(t), right(t));
	 free(t);
	 t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, Item it) {

   printf("Not yet implemented.\n");
   
   return t;
}

Tree partition(Tree t, int i, int plvl) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));

      for(int j=0; j<plvl; j++){ printf("  ");}

      //printf("lvl=%d, i=%d , m=%d \n", lvl, i, m);
      if (i < m) {
         printf("[%d](i(%d)<m(%d)): plvl=%d \n", t->data, i, m, plvl);
	 left(t) = partition(left(t), i, plvl+1);
	 printf("rotateRight at %d \n", data(t));
	 t = rotateRight(t);
      } else if (i > m) {
         printf("[%d](i(%d)>m(%d)): (i-m-1)=%d , plvl=%d\n", t->data, i, m, i-m-1, plvl);
	 right(t) = partition(right(t), i-m-1, plvl+1 );
	 printf("rotateLeft at %d \n", data(t));
	 t = rotateLeft(t);
      }
      else {
         printf("[%d](i(%d)==m(%d)): plvl=%d \n", t->data,  i, m, plvl);
      }
   }
   return t;
}

Tree rebalance(Tree t, int lvl) {
   printf(">>>>>>>>> Start level: %d \n", lvl);

   int n = TreeNumNodes(t);
   if (n >= 3) {
      int curRoot = t->data;
      printf("###### Start partitioning at root %d \n", curRoot);
      t = partition(t, n/2, 0);               // put node with median key at root
      printf("###### After partitioning at root %d \n", curRoot);
      showTree(t);

      int leftRoot = data(left(t));
      printf("++++++++ Start rebalance at root %d \n", leftRoot);
      left(t) = rebalance(left(t), lvl+1);    // then rebalance each subtree
      printf("++++++++ End rebalance at root %d \n", leftRoot);

      int rightRoot = data(right(t));
      printf("++++++++ Start rebalance at root %d \n", rightRoot);
      right(t) = rebalance(right(t), lvl+1);
      printf("++++++++ End rebalance at root %d \n", rightRoot);
   }
   else {
	printf("    n < 3 \n");
   }

   printf(">>>>>>>>> End level: %d \n", lvl);

   return t;
}


int myCountEven(Tree t){

   if(t == NULL) { return 0; }

   int lc = myCountEven(t->left);
   int rc = myCountEven(t->right);

   int ans; 
   // process the current node
   if(t->data % 2 == 0) {
      ans = rc + lc + 1;
   }
   else {
      ans = rc + lc ;
   }

   return ans;

}



void myPrint(Tree t){

   if(t == NULL ) { return; }

   printf("%d , ", t->data);

   myPrint(t->left);


   myPrint(t->right);




}


















