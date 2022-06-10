
#include "list.h"

void reverseDLList(List l) {
	Node tmp = NULL;
	for (Node curr = l->first; curr != NULL; curr = curr->prev) {
		// swap prev and next
		tmp = curr->next;
		curr->next = curr->prev;
		curr->prev = tmp;
	}
	// swap head and tail in list representation
	tmp = l->first;
	l->first = l->last;
	l->last = tmp;
}

