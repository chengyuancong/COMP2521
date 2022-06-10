
#include "list.h"

int listDeleteLargest(List l) {
	Node head = l->head;
	Node max = head;
	Node currPrev = NULL;
	Node maxPrev = NULL;
	int num = 0;
	for (Node curr = head; curr != NULL; currPrev = curr, curr = curr->next) {
		if (curr->value > max->value) {
			max = curr;
			maxPrev = currPrev;
		}
	}
	if (maxPrev == NULL) {
		num = head->value;
		l->head = head->next;
		free(head);
	} else {
		maxPrev->next = max->next;
		num = max->value;
		free(max);
	}
	return num;
}

