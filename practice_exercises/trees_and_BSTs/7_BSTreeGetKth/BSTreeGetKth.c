
#include <stdlib.h>

#include "BSTree.h"

static int BSTreeNodeNums(BSTree t);

int BSTreeGetKth(BSTree t, int k) {
	int index = BSTreeNodeNums(t->left);
	if (k < index) {
		return BSTreeGetKth(t->left, k);
	} else if (k > index) {
		return BSTreeGetKth(t->right, k-index-1);
	} else {
		return t->value;
	}
}

static int BSTreeNodeNums(BSTree t) {
	if (t == NULL) {
		return 0;
	}
	return 1 + BSTreeNodeNums(t->left) + BSTreeNodeNums(t->right);
}