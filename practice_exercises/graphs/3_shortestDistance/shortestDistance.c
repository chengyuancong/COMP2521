
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

static int getDist(int *visited, int src, int dest);

int shortestDistance(Graph g, int src, int dest) {
	int nV = GraphNumVertices(g);
	int *visited = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		visited[i] = -1;
	}
	Queue q = QueueNew();
	visited[src] = src;
	QueueEnqueue(q, src);
	while (!QueueIsEmpty(q)) {
		int curr = QueueDequeue(q);
		if (curr == dest) {
			break;
		} 
		for (int i = 0; i < nV; i++) {
			if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
				visited[i] = curr;
				QueueEnqueue(q, i);
			}
		}
	}
	int dist = visited[dest] == -1 ? -1 : getDist(visited, src, dest);
	QueueFree(q);
	free(visited);
	return dist;
}

static int getDist(int *visited, int src, int dest) {
	int dist = 0;
	for (int curr = dest; curr != src; curr = visited[curr]) {
		dist++;
	}
	return dist;
}