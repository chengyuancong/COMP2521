// Centrality Measures API implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"

#define INFINITY INT_MAX

static int countPathNum(ShortestPaths sps, int** pathNums, Vertex src, Vertex dest);

NodeValues closenessCentrality(Graph g) {
	// Initialise NodeValues
	NodeValues nvs;
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = malloc(nvs.numNodes * sizeof(double));

	// Calculate Closeness Centrality via every vertex's sps
	for (Vertex u = 0; u < nvs.numNodes; u++) {
		ShortestPaths sps = dijkstra(g, u);
		double n = 0;
		double distSum = 0;
		for (Vertex v = 0; v < nvs.numNodes; v++) {
			// If v is reachable from u
			if (sps.dist[v] != INFINITY) {
				n++;
				distSum += sps.dist[v];
			}
		}

		// Whether u is isolated
		nvs.values[u] = (n == 1) ? 0 : (n-1)/(nvs.numNodes-1) * (n-1)/distSum;
		freeShortestPaths(sps);
	}
	return nvs;
}

NodeValues betweennessCentrality(Graph g) {
	// Initialise NodeValues
	NodeValues nvs;
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = malloc(nvs.numNodes * sizeof(double));

	// sps for every vertex in the graph
	ShortestPaths spss[nvs.numNodes];
	for (Vertex v = 0; v < nvs.numNodes; v++) {
		spss[v] = dijkstra(g, v);
	}
	
	// Initialise path num grids, 
	// pathNum[s][t] is num of paths from i to j
	int** pathNums = malloc(nvs.numNodes * sizeof(int*));
	for (int i = 0; i < nvs.numNodes; i++) {
		pathNums[i] = malloc(nvs.numNodes * sizeof(int));
	}
	for (Vertex s = 0; s < nvs.numNodes; s++) {
		for (Vertex t = 0; t < nvs.numNodes; t++) {
			pathNums[s][t] = (s == t) ? 1 : 0;
		}
	}

	// count path numbers for any s and t in this graph
	for (Vertex s = 0; s < nvs.numNodes; s++) {
		for (Vertex t = 0; t < nvs.numNodes; t++) {
			pathNums[s][t] = countPathNum(spss[s], pathNums, s, t);
		}
	}

	// Calculate Betweenness Centrality for any vertex v in graph
	for (Vertex v = 0; v < nvs.numNodes; v++) {
		double sum = 0;
		for (Vertex s = 0; s < nvs.numNodes; s++) {
			if (s != v) {
				for (Vertex t = 0; t < nvs.numNodes; t++) {
					if (t != v && t != s) {
						// If t is reachable from s and path from s to t passes v
						if (spss[s].dist[t] != INFINITY 
						&& spss[s].dist[v] + spss[v].dist[t] == spss[s].dist[t]) {
							sum += (pathNums[s][v]*pathNums[v][t])/((double)pathNums[s][t]);
						}
					}
				}
			}
		}
		nvs.values[v] = sum;
	}

	// Free pathNums
	for (int i = 0; i < nvs.numNodes; i++) {
		free(pathNums[i]);
	}
	free(pathNums);

	// Free spss
	for (Vertex v = 0; v < nvs.numNodes; v++) {
		freeShortestPaths(spss[v]);
	}

	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	NodeValues nvs = betweennessCentrality(g);
	// Normalise
	for (Vertex v = 0; v < nvs.numNodes; v++) {
		nvs.values[v] = nvs.values[v]/((nvs.numNodes-1)*(nvs.numNodes-2));
	}
	return nvs;
}

void showNodeValues(NodeValues nvs) {
	for (Vertex v = 0; v < nvs.numNodes; v++) {
		printf("%d: %.6lf\n", v, nvs.values[v]);
	}
}

void freeNodeValues(NodeValues nvs) {
	free(nvs.values);
}

static int countPathNum(ShortestPaths sps, int** pathNums, Vertex src, Vertex dest) {
	// Dynamically update path num for any src and dest.
	// If haven't calculated, recursively calculate for any pred node.
	if (pathNums[src][dest] == 0) {
		for (PredNode* curr = sps.pred[dest]; curr != NULL; curr = curr->next) {
			pathNums[src][dest] += countPathNum(sps, pathNums, src, curr->v);
		}
	}
	return pathNums[src][dest];
}
