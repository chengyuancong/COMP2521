
#include "BSTree.h"

#include <stdlib.h>

static BSTree doGetSmallest(BSTree t);

BSTree BSTreeGetSmallest(BSTree t) {
	return t == NULL ? NULL : doGetSmallest(t);
}

static BSTree doGetSmallest(BSTree t) {
	// recursive
	if (t->left == NULL) {
		return t;
	} else {
		return doGetSmallest(t->left);
	}
	
	/* // iterative
	BSTree curr = t;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	return curr; */
}