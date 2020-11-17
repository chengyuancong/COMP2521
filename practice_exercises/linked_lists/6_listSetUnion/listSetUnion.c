
#include "list.h"

static bool listContain(Node head, int value);
static Node listAppend(Node head, int value);

List listSetUnion(List s1, List s2) {
	List new = newList();
	for (Node curr = s1->head; curr != NULL; curr = curr->next) {
		if (!listContain(new->head, curr->value)) {
			new->head = listAppend(new->head, curr->value);
		}
	}
	for (Node curr = s2->head; curr != NULL; curr = curr->next) {
		if (!listContain(new->head, curr->value)) {
			new->head = listAppend(new->head, curr->value);
		}
	}
	return new;
}

static bool listContain(Node head, int value) {
	while (head != NULL) {
		if (head->value == value) {
			return true;
		}
		head = head->next;
	}
	return false;
}

static Node listAppend(Node head, int value) {
	// recursive
	if (head == NULL) {
		return newNode(value);
	} else {
		head->next = listAppend(head->next, value);
		return head;
	}
	/*
	// iterative
	if (head == NULL) {
		return newNode(value);
	} else {
		Node curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newNode(value);
	}
	return head;
	*/
}