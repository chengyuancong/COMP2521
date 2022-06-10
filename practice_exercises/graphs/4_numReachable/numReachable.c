
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static int doNumReachable(Graph g, int curr, int nV, int *visited);
// static void doDFS(Graph g, int curr, int nV, int *visited);
// static int getVisitedNum(int *visited, int nV);

int numReachable(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *visited = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		visited[i] = -1;
	}
	visited[src] = src;
	int num = doNumReachable(g, src, nV, visited);
	free(visited);
	return num;
}

static int doNumReachable(Graph g, int curr, int nV, int *visited) {
	int num = 1;
	for (int i = 0; i < nV; i++) {
		if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
			visited[i] = curr;
			num += doNumReachable(g, i, nV, visited);
		}
	}
	return num;
}

// alternatively, do dfs and check visited[]
/* int numReachable(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *visited = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		visited[i] = -1;
	}
	visited[src] = src;
	doDFS(g, src, nV, visited);
	int num = getVisitedNum(visited, nV);
	free(visited);
	return num;
}

static void doDFS(Graph g, int curr, int nV, int *visited) {
	for (int i = 0; i < nV; i++) {
		if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
			visited[i] = curr;
			doDFS(g, i, nV, visited);
		}
	}
}

static int getVisitedNum(int *visited, int nV) {
	int num = 0;
	for (int i = 0; i < nV; i++) {
		if (visited[i] != -1) {
			num++;
		}
	}
	return num;
} */