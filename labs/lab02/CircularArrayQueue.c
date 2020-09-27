// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	if ((q->frontIndex + q->size) % q->capacity == q->frontIndex) {
		q->items = realloc(q->items, 2 * q->capacity * sizeof(int));
		if (q == NULL) {
			fprintf(stderr, "couldn't reallocate Queue");
			exit(EXIT_FAILURE);
		}
		for (int i = q->capacity, j = 0; i < (q->frontIndex + q->capacity); i++, j++) {
			q->items[i] = q->items[j];
		}
		q->items[q->frontIndex + q->size] = it;
		q->size++;
		q->capacity = 2 * q->capacity;
	} else {
		q->items[(q->frontIndex + q->size) % q->capacity] = it;
		q->size++;
	}
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	Item head = q->items[q->frontIndex];
	q->frontIndex = (q->frontIndex + 1) % q->capacity;
	q->size--;
	return head;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);
	
	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
}

