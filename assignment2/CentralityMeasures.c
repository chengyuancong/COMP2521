// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"

// 2d array for storing the number of shortest path between two vertex
static int **pathNum = NULL;
// pred list array for current src
static PredNode **preds = NULL;
// src and dest in recursively restoring path from t to s
static Vertex src = 0;
static Vertex dest = 0;


// Helper functions for counting numbers of shortest paths
static void initialisePathNum(int n);
static void freePathNum(int n);
static void countPathNum(Vertex curr);


NodeValues closenessCentrality(Graph g) {
	int N = GraphNumVertices(g); 		// number of nodes in the graph.
	NodeValues nvs;
	nvs.numNodes = N;
	nvs.values = malloc(N * sizeof(double));
	for (int i = 0; i < N; i++){
		double n = 0;					// number of nodes that Vertex i can reach
		double distSum = 0;				// sum of shortest-path distance for i can reach j
		ShortestPaths sps = dijkstra(g, i);
		for (int j = 0; j < N; j++) {
			distSum += sps.dist[j];
			if (sps.dist[j] != 0) n++;
		}
		n++;							// n should includes itself
		if (distSum == 0) {
			nvs.values[i] = 0;
		} else {
			nvs.values[i] = ((n-1)/(N-1)) * ((n-1)/distSum);
		}
		freeShortestPaths(sps);
	}
	return nvs;
}

NodeValues betweennessCentrality(Graph g) {
	int n = GraphNumVertices(g);	// the number of nodes in the graph	
	NodeValues nvs;
	nvs.numNodes = n;
	nvs.values = malloc(n * sizeof(double));
	// store every vertice's sps in a list
	ShortestPaths *spss = malloc(n * sizeof(ShortestPaths));
	for (Vertex i = 0; i < n; i++) {
		spss[i] = dijkstra(g, i);
	}
	// initialise pathNum[][]
	initialisePathNum(n);
	// count paths from any s to t in this graph (s != t)
	for (Vertex s = 0; s < n; s++) {
		preds = spss[s].pred;
		for (Vertex t = 0; t < n; t++) {
			if (s != t) {
				dest = t;
				src = s;
				countPathNum(dest);
			}
		}
	}
	// calculate betweennessCentrality for every v
	for (Vertex v = 0; v < n; v++) {
		double quotientSum = 0;
		for (Vertex s = 0; s < n; s++) {
			if (s != v) {
				for (Vertex t = 0; t < n; t++) {
					if (t != v && t != s) {
						double st =  pathNum[s][t];
						double stv = 0;
						if (spss[s].dist[v] + spss[v].dist[t] == spss[s].dist[t]) {
							stv = pathNum[s][v] * pathNum[v][t];
						}
						if (st != 0) {
							quotientSum += stv/st;
						}
					}
				}
			}
		}
		nvs.values[v] = quotientSum;
	}
	freePathNum(n);
	// free spss
	for (Vertex i = 0; i < n; i++) {
		freeShortestPaths(spss[i]);
	}
	free(spss);
	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	int n = GraphNumVertices(g);	// the number of nodes in the graph		
	NodeValues nvs;
	nvs.numNodes = n;
	nvs.values = malloc(n * sizeof(double));
	NodeValues unnormalised = betweennessCentrality(g);
	for (Vertex i = 0; i < n; i++) {
		nvs.values[i] = unnormalised.values[i] / ((n-1) * (n-2));
	}
	freeNodeValues(unnormalised);
	return nvs;
}

void showNodeValues(NodeValues nvs) {
	for (Vertex i = 0; i < nvs.numNodes; i++) {
		printf("%d: %.6lf\n", i, nvs.values[i]);
	}
}

void freeNodeValues(NodeValues nvs) {
	free(nvs.values);
}



// Helper functions for counting numbers of shortest paths
static void initialisePathNum(int n) {
	pathNum = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		pathNum[i] = calloc(n, sizeof(int));
	}
}

static void countPathNum(Vertex curr) {
	if (curr == src) {
		pathNum[src][dest]++;
	} else {
		for (PredNode *pred = preds[curr]; pred != NULL; pred = pred->next) {
			countPathNum(pred->v);
		}
	}
}

static void freePathNum(int n) {
	for (int i = 0; i < n; i++) {
		free(pathNum[i]);
	}
	free(pathNum);
}
