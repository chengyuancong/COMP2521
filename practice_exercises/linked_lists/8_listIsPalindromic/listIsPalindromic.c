
#include "list.h"

bool listIsPalindromic(List l) {
	int remainedPairs = l->size/2;
	Node head = l->first;
	Node tail = l->last;
	while (remainedPairs > 0) {
		if (head->value != tail->value) {
			return false;
		}
		head = head->next;
		tail = tail->prev;
		remainedPairs--;
	}
	return true;
}

