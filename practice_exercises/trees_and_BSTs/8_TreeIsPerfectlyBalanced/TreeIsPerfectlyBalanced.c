
#include <stdlib.h>
#include <math.h>
#include "tree.h"

static int BSTreeNodeNums(Tree t);

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
		return true;
	}
	int numL = BSTreeNodeNums(t->left);
	int numR = BSTreeNodeNums(t->right);
	if (abs(numL-numR) <= 1) {
		bool balancedL = TreeIsPerfectlyBalanced(t->left);
		bool balancedR = TreeIsPerfectlyBalanced(t->right);
		return balancedL && balancedR;
	} else {
		return false;
	}
}

static int BSTreeNodeNums(Tree t) {
	if (t == NULL) {
		return 0;
	}
	return 1 + BSTreeNodeNums(t->left) + BSTreeNodeNums(t->right);
}