
#include "list.h"

void listReverse(List l) {
	Node head = l->head;
	if (head != NULL && head->next != NULL) {
		// use first node as tail
		Node newList = head;
		Node remained = head->next;
		newList->next = NULL;
		while (remained != NULL) {
			Node newHead = remained;
			remained = remained->next;
			newHead->next = newList;
			newList = newHead;
		}
		l->head = newList;
	}
}

