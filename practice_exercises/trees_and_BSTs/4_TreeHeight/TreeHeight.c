
#include <stdlib.h>

#include "tree.h"

static int max(int a, int b);

int TreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    return max(TreeHeight(t->left), TreeHeight(t->right))+1;
}

static int max(int a, int b) {
    return a > b ? a : b;
}
