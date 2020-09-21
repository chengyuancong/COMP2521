// Set.c ... Set ADT implementation
// Written by John Shepherd, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Bool.h"
#include "Set.h"

// concrete data structure
typedef struct Node {
	int  value;
	struct Node *next;
} Node;
struct SetRep {
	int   nelems;
	Node *elems;
};

// Local functions

// check whether Set looks plausible
int isValid(Set s)
{
	if (s == NULL) return FALSE;
	// if (s->elems == NULL) return 1; // empty set
	return TRUE;
}

// Interface functions

// create new empty set
Set newSet()
{
	Set new;
	if ((new = malloc(sizeof(struct SetRep))) == NULL) {exit(1);}
	new->nelems = 0;
	new->elems = NULL;
	return new;
}

// free memory used by set
void dropSet(Set s)
{
	// assert(isValid(s));
}

// make a copy of a set
Set SetCopy(Set s)
{
	// assert(isValid(s));
	return NULL;
}

// add value into set
void SetInsert(Set s, int n)
{
	// assert(isValid(s));
	Node *cur;
	for (cur = s->elems; cur != NULL; cur = cur->next)
		if (cur->value == n) return;
	Node *new;
	if ((new = malloc(sizeof(Node))) == NULL) { exit(1); }
	new->value = n;
	new->next = s->elems;
	s->elems = new;
	s->nelems++;
}

// remove value from set
void SetDelete(Set s, int n)
{
	// assert(isValid(s));
}

// set membership test
int SetMember(Set s, int n)
{
	// assert(isValid(s));
	return 0;
}

// union
Set SetUnion(Set s, Set t)
{
	// assert(isValid(s) && isValid(t));
	return NULL;
}

// intersection
Set SetIntersect(Set s, Set t)
{
	// assert(isValid(s) && isValid(t));
	return NULL;
}

// cardinality (#elements)
int SetCard(Set s)
{
	// assert(isValid(s));
	return 0;
}

// display set as {i1,i2,i3,...iN}
void showSet(Set s)
{
	// assert(isValid(s));
	printf("{");
	Node *cur;
	for (cur = s->elems; cur != NULL; cur = cur->next) {
		printf("%d", cur->value);
		if (cur->next != NULL) printf(",");
	}
	printf("}");
}

// read+insert set values
void readSet(FILE *in, Set s)
{
	// assert(isReadable(in) && isValid(s));
}
