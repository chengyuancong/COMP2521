
#include "tree.h"

static Tree doTreeCopy(Tree t, int depth, int currDepth);
static Tree newNode(int val);


Tree TreeCopy(Tree t, int depth) {
	if (t == NULL || depth < 0) {
		return NULL;
	}
	return doTreeCopy(t, depth, 0);
}

static Tree doTreeCopy(Tree t, int depth, int currDepth) {
	Tree new = NULL;
	if (t != NULL && currDepth <= depth) {
		new = newNode(t->value);
		new->left = doTreeCopy(t->left, depth, currDepth+1);
		new->right = doTreeCopy(t->right, depth, currDepth+1);
	}
	return new;
}

static Tree newNode(int val) {
	Tree new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	new->value = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}
