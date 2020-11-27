
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *visited = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		visited[i] = -1;
	}
	Queue q = QueueNew();
	visited[src] = src;
	QueueEnqueue(q, src);
	while(!QueueIsEmpty(q)) {
		int curr = QueueDequeue(q);
		printf("%d ", curr);
		for (int i = 0; i < nV; i++) {
			if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
				visited[i] = curr;
				QueueEnqueue(q, i);
			}
		}
	}
	QueueFree(q);
	free(visited);
}

