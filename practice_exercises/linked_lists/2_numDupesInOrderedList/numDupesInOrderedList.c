
#include "list.h"

int numDupesInOrderedList(List l) {
	Node head = l->head;
	if (head == NULL || head->next == NULL) {
		return 0;
	} else {
		int num = head->value;
		int duplicated = 0;
		Node curr = head->next;
		while (curr != NULL) {
			if (curr->value == num) {
				duplicated++;
			} else {
				num = curr->value;
			}
			curr = curr->next;
		}
		return duplicated;
	}
}

