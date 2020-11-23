
#include "list.h"

int numDupesInOrderedList(List l) {
	Node head = l->head;
	int duplicated = 0;
	if (head != NULL && head->next != NULL) {
		int num = head->value;
		Node curr = head->next;
		while (curr != NULL) {
			if (curr->value == num) {
				duplicated++;
			} else {
				num = curr->value;
			}
			curr = curr->next;
		}
	}
	return duplicated;
}

