
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static void doDFS(Graph g, int curr, int *visited, int nV);

void depthFirstSearch(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *visited = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		visited[i] = -1;
	}
	visited[src] = src;
	doDFS(g, src, visited, nV);
	free(visited);
}

static void doDFS(Graph g, int curr, int *visited, int nV) {
	printf("%d ", curr);
	for (int i = 0; i < nV; i++) {
		if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
			visited[i] = curr;
			doDFS(g, i, visited, nV);
		}
	} 
}