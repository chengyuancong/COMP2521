// Implementation of the BST ADT using an AVL tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Time.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
    Time time;
    int  height;
    Node left;
    Node right;
};

struct tree {
    Node root;
};


////////////////////////////////////////////////////////////////////////
// Function Prototypes

static void doFree(Node n);
static Node doInsert(Node n, Time time);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Time time);
static Time doTreeFloor(Node n, Time time, Time closest);
static Time doTreeCeiling(Node n, Time time, Time closest);

////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

// Creates a new empty tree
Tree TreeNew(void) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

// Frees all memory associated with the given tree
void TreeFree(Tree t) {
    doFree(t->root);
    free(t);
}

static void doFree(Node n) {
    if (n != NULL) {
        doFree(n->left);
        doFree(n->right);
        TimeFree(n->time);
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Insertion

// Inserts  a  copy of the given time into the tree if it is not already
// in the tree
void TreeInsert(Tree t, Time time) {
    t->root = doInsert(t->root, time);
}

static Node doInsert(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    // insert recursively
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsert(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, time);
    } else { // (cmp == 0)
        // if time is already in the tree,
        // we can return straight away
        return n;
    }

    // insertion done
    // fix the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));
    
    // rebalance the tree
    int left_height = height(n->left);
    int right_height = height(n->right);
    if (left_height - right_height > 1) {
        if (TimeCmp(time, n->left->time) > 0) {
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    } else if (right_height - left_height > 1) {
        if (TimeCmp(time, n->right->time) < 0) {
            n->right = rotateRight(n->right);
        }
        n = rotateLeft(n);
    }
    return n;
}

static Node newNode(Time time) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    n->time = TimeCopy(time);
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Rotates  the  given  subtree left and returns the root of the updated
// subtree.
static Node rotateLeft(Node n) {
    if (n == NULL || n->right == NULL) {
        return n;
    }
    Node n2 = n->right;
    n->right = n2->left;
    n2->left = n;
    n->height = 1 + max(height(n->left), height(n->right));
    n2->height = 1 + max(height(n2->left), height(n2->right));
    return n2;
}

// Rotates the given subtree right and returns the root of  the  updated
// subtree.
static Node rotateRight(Node n) {
    if (n == NULL || n->left == NULL) {
        return n;
    }
    Node n2 = n->left;
    n->left = n2->right;
    n2->right = n;
    n->height = 1 + max(height(n->left), height(n->right));
    n2->height = 1 + max(height(n2->left), height(n2->right));
    return n2;
}

// Returns  the height of a subtree while assuming that the height field
// of the root node of the subtree is correct
static int height(Node n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////////////////
// Specialised Operations

// Returns the latest time in the tree that is earlier than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeFloor(Tree t, Time time) {
    return doTreeFloor(t->root, time, NULL);
}

// Returns the earliest time in the tree that is later than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeCeiling(Tree t, Time time) {
    return doTreeCeiling(t->root, time, NULL);
}

static Time doTreeFloor(Node n, Time time, Time closest) {
    if (n == NULL) {
        return closest;
    }
    if (TimeCmp(n->time, time) == 0) {
        return n->time;
    } else if (TimeCmp(n->time, time) < 0) {
        return doTreeFloor(n->right, time, n->time);
    } else {
        return doTreeFloor(n->left, time, closest);
    }
}

static Time doTreeCeiling(Node n, Time time, Time closest) {
    if (n == NULL) {
        return closest;
    }
    if (TimeCmp(n->time, time) == 0) {
        return n->time;
    } else if (TimeCmp(n->time, time) > 0) {
        return doTreeCeiling(n->left, time, n->time);
    } else {
        return doTreeCeiling(n->right, time, closest);
    }
}

////////////////////////////////////////////////////////////////////////
// Printing

//////////////////
// List the items

static void doList(Node n);

void TreeList(Tree t) {
    doList(t->root);
}

static void doList(Node n) {
    if (n != NULL) {
        doList(n->left);
        TimeShow(n->time);
        printf("\n");
        doList(n->right);
    }
}

///////////////////////////
// Show the tree structure

typedef unsigned long long uint64;
static void doShow(Node n, int level, uint64 arms);

void TreeShow(Tree t) {
    if (t->root != NULL && t->root->height >= 64) {
        printf("Tree is too tall!\n");
    } else {
        doShow(t->root, 0, 0);
    }
}

// This  function  uses a hack to determine when to draw the arms of the
// tree and relies on the tree being reasonably balanced. Don't  try  to
// use this function if the tree is not an AVL tree!
static void doShow(Node n, int level, uint64 arms) {
    if (n == NULL) return;

    TimeShow(n->time);
    printf(" (height: %d)\n", n->height);

    if (n->left != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("%s", n->right != NULL ? "┝━╸L: " : "┕━╸L: ");
        if (n->right != NULL) {
            arms |= (1LLU << level);
        } else {
            arms &= ~(1LLU << level);
        }
        doShow(n->left, level + 1, arms);
    }

    if (n->right != NULL) {
        // if (n->left != NULL) {
        //     for (int i = 0; i <= level; i++) {
        //         if ((1LLU << i) & arms) {
        //             printf("│     ");
        //         } else {
        //             printf("      ");
        //         }
        //     }
        //     printf("\n");
        // }
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("┕━╸R: ");
        arms &= ~(1LLU << level);
        doShow(n->right, level + 1, arms);
    }
}

////////////////////////////////////////////////////////////////////////
// Testing
// All  functions below exist for testing purposes ONLY. Do NOT use them
// in your code.

static Node doInsertLeaf(Node n, Time time);

void TreeRotateLeftAtRoot(Tree t) {
    t->root = rotateLeft(t->root);
}

void TreeRotateRightAtRoot(Tree t) {
    t->root = rotateRight(t->root);
}

void TreeInsertLeaf(Tree t, Time time) {
    t->root = doInsertLeaf(t->root, time);
}

static Node doInsertLeaf(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsertLeaf(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsertLeaf(n->right, time);
    }

    n->height = 1 + max(height(n->left), height(n->right));
    return n;
}
