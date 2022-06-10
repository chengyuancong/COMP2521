
#include "list.h"


static Node doListReverse(Node head);

void listReverse(List l) {
	Node head = l->head;
	if (head != NULL && head->next != NULL) {
		l->head = doListReverse(head);
	}
}

static Node doListReverse(Node head) {
	if (head->next == NULL) {
		return head;
	}
	Node last = doListReverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return last;
}


// iteratively
/* void listReverse(List l) {
	Node head = l->head;
	if (head != NULL && head->next != NULL) {
		Node curr = l->head;
		Node prev = NULL;
		Node remained = NULL;
		while (curr != NULL) {
			remained = curr->next;
			curr->next = prev;
			prev = curr;
			curr = remained;
		}
		l->head = prev;
	}
} */
