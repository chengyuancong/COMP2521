
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

static BSTree newBSTNode(int val);

BSTree BSTreeInsert(BSTree t, int val) {
	if (t == NULL) {
		return newBSTNode(val);
	} else if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
		return t;
	} else if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
		return t;
	} else {
		return t;
	}
}

static BSTree newBSTNode(int val) {
	BSTree new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	new->value = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}