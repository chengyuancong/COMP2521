
#include "list.h"

bool listIsOrdered(List l) {
	Node head = l->head;
	if (head == NULL || head->next == NULL || head->next->next == NULL) {
		return true;
	} else {
		Node curr = head;
		Node next = head->next;
		int seq = 0;
		while (next != NULL) {
			if (curr->value != next->value) {
				seq = next->value - curr->value;		// > 0 if assending, < 0 dessending
				break;
			}
			curr = curr->next;
			next = next->next;
		}
		if (seq == 0) {						// all equal
			return true;
		} else {							// not all equal
			while (next != NULL) {
				if (curr->value != next->value && (next->value - curr->value)*seq < 0) {
					return false;
				}
				curr = curr->next;
				next = next->next;
			}
		}
		return true;
	}
}


