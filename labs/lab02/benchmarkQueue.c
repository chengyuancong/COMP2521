
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();
	
	// enqueue 160000
	for (int i = 1; i <= 160000; i++) {
		QueueEnqueue(q, i);
	}
	
	// dequeue 1 to 80000, enqueue 160001 to 240000
	for (int i = 160001, j = 1; i <= 240000; i++, j++) {
		QueueEnqueue(q, i);
		QueueDequeue(q);
	}
	
	QueueFree(q);
}

