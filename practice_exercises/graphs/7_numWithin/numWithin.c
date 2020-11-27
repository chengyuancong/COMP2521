
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

static void doBFS(Graph g, int curr, int nV, int *distList, int *visited);
// static void doDFS(Graph g, int curr, int nV, int *distList, int *visited);
static int getNum(int *distList, int nV, int dist);

int numWithin(Graph g, int src, int dist) {
	int nV = GraphNumVertices(g);
	int *distList = malloc(nV * sizeof(int));
	int *visited  = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		distList[i] = -1;
		visited[i] = -1;
	}
	distList[src] = 0;
	visited[src] = src;
	doBFS(g, src, nV, distList, visited);
	// alternatively, use DFS
	// doDFS(g, src, nV, distList, visited);
	int num = getNum(distList, nV, dist);
	free(distList);
	free(visited);
	return num;
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

static int getNum(int *distList, int nV, int dist) {
	int num = 0;
	for (int i = 0; i < nV; i++) {
		if (distList[i] >= 0 && distList[i] <= dist) {
			num++;
		}
	}
	return num;
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