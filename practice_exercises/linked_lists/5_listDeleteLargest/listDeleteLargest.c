
#include "list.h"

int listDeleteLargest(List l) {
	Node head = l->head;
	Node max = head;
	int num = 0;
	for (Node curr = head; curr != NULL; curr = curr->next) {
		if (curr->value > max->value) {
			max = curr;
		}
	}
	if (max == head) {
		num = head->value;
		l->head = head->next;
		free(head);
	} else {
		Node prev = head;
		while (prev->next != max) {
			prev = prev->next;
		}
		prev->next = max->next;
		num = max->value;
		free(max);
	}
	return num;
}

