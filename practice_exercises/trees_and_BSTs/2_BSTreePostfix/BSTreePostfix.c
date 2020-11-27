
#include <stdio.h>

#include "BSTree.h"

void BSTreePostfix(BSTree t) {
	if (t != NULL) {
		BSTreePostfix(t->left);
		BSTreePostfix(t->right);
		printf("%d ", t->value);
	}
}
