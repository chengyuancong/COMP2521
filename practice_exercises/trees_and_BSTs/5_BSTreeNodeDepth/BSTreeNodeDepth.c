
#include <stdlib.h>

#include "BSTree.h"

static int doBSTreeNodeDepth(BSTree t, int key, int depth);

int BSTreeNodeDepth(BSTree t, int key) {
	return doBSTreeNodeDepth(t, key, 0);
}

static int doBSTreeNodeDepth(BSTree t, int key, int depth) {
	if (t == NULL) {
		return -1;
	}
	if (key > t->value) {
		return doBSTreeNodeDepth(t->right, key, depth+1);
	} else if (key < t->value) {
		return doBSTreeNodeDepth(t->left, key, depth+1);
	} else {
		return depth;
	}
}