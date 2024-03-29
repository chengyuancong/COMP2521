
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

static void testQueue1(void);
static void testQueue2(void);
static void testQueue3(void);
static void testQueue4(void);

int main(void) {
	testQueue1();
	testQueue2();
	testQueue3();
	testQueue4();
	
	printf("All tests passed!\n");
}

// tests general enqueueing and dequeueing
static void testQueue1(void) {
	Queue q = QueueNew();
	
	// enqueue 1 to 10
	for (int i = 1; i <= 10; i++) {
		QueueEnqueue(q, i);
		assert(QueueSize(q) == i);
	}
	
	// dequeue 1 to 5
	for (int j = 1; j <= 5; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 5);
	
	// enqueue 11 to 20, dequeue 6 to 15
	for (int i = 11, j = 6; i <= 20; i++, j++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 5);
	
	// dequeue 16 to 20
	for (int j = 16; j <= 20; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 0);
	assert(QueueIsEmpty(q));
	
	// enqueue a number
	QueueEnqueue(q, 21);
	assert(QueueFront(q) == 21);
	
	QueueFree(q);
}

// tests enqueueing and dequeueing at capacity
static void testQueue2(void) {
	Queue q = QueueNew();
	
	// enqueue 16
	for (int i = 1; i <= 16; i++) {
		QueueEnqueue(q, i);
		assert(QueueSize(q) == i);
	}
	
	// dequeue 1 to 8, enqueue 17 to 24
	for (int i = 17, j = 1; i <= 24; i++, j++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	
	assert(QueueSize(q) == 16);
	QueueFree(q);
}

static void testQueue3(void) {
	Queue q = QueueNew();
	
	// enqueue 1 to 100
	for (int i = 1; i <= 100; i++) {
		QueueEnqueue(q, i);
		assert(QueueSize(q) == i);
	}
	
	// dequeue 1 to 50
	for (int j = 1; j <= 50; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 50);
	
	// enqueue 101 to 150, dequeue 51 to 100
	for (int i = 101, j = 51; i <= 150; i++, j++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 50);
	
	// dequeue 101 to 120
	for (int j = 101; j <= 120; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 30);
	
	// dequeue 121 to 150
	for (int j = 121; j <= 150; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueIsEmpty(q));
	
	// enqueue a number
	QueueEnqueue(q, 151);
	assert(QueueFront(q) == 151);
	
	QueueFree(q);
}

static void testQueue4(void) {
	Queue q = QueueNew();
	
	// enqueue 1600
	for (int i = 1; i <= 1600; i++) {
		QueueEnqueue(q, i);
		assert(QueueSize(q) == i);
	}
	
	// dequeue 1 to 800, enqueue 1601 to 2400
	for (int i = 1601, j = 1; i <= 2400; i++, j++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	
	assert(QueueSize(q) == 1600);
	QueueFree(q);
}