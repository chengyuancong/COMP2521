
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    int heightL = TreeHeight(t->left);
    int heightR = TreeHeight(t->right);
    if (heightL > heightR) {
        return heightL + 1;
    } else {
        return heightR + 1;
    }
}
