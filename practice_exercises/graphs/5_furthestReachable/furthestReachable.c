
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

static void doBFS(Graph g, int curr, int nV, int *dist, int *visited);
// static void doDFS(Graph g, int curr, int nV, int *dist, int *visited);
static int getFurthest(int src, int *dist, int nV);


int furthestReachable(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *dist = malloc(nV * sizeof(int));
	int *visited  = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		dist[i] = -1;
		visited[i] = -1;
	}
	dist[src] = 0;
	visited[src] = src;
	doBFS(g, src, nV, dist, visited);
	// alternatively, use DFS
	// doDFS(g, src, nV, dist, visited);
	int furthest = getFurthest(src, dist, nV);
	free(dist);
	free(visited);
	return furthest;
}

static void doBFS(Graph g, int src, int nV, int *dist, int *visited) {
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	while (!QueueIsEmpty(q)) {
		int curr = QueueDequeue(q);
		for (int i = 0; i < nV; i++) {
			if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
				visited[i] = curr;
				dist[i] = dist[curr]+1;
				QueueEnqueue(q, i);
			}
		}
	}
	QueueFree(q);
}

static int getFurthest(int src, int *dist, int nV) {
	int max = dist[src];
	int furthest = src;
	for (int i = 0; i < nV; i++) {
		if (dist[i] >= max) {
			max = dist[i];
			furthest = i;
		}
	}
	return furthest;
}

// alternatively, use DFS
/* static void doDFS(Graph g, int curr, int nV, int *dist, int *visited) {
	for (int i = 0; i < nV; i++) {
		if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
			visited[i] = curr;
			if (dist[i] == -1 || dist[curr]+1 < dist[i]) {
				dist[i] = dist[curr]+1;
			}
			doDFS(g, i, nV, dist, visited);
			visited[i] = -1;
		}
	}
} */
