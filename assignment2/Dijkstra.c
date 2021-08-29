// Dijkstra API implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Dijkstra.h"
#include "PQ.h"

#define INFINITY INT_MAX

static PredNode* PredNodeNew(Vertex v);
static PredNode* PredListAppend(PredNode* head, Vertex v);
static void PredListFree(PredNode* head);

ShortestPaths dijkstra(Graph g, Vertex src) {
	ShortestPaths sps;

	// Initialise sps
	sps.numNodes = GraphNumVertices(g);;
	sps.src = src;
	sps.dist = malloc(sps.numNodes * sizeof(int));
	sps.pred = malloc(sps.numNodes * sizeof(PredNode*));
	for (Vertex v = 0; v < sps.numNodes; v++) {
		sps.dist[v] = INFINITY;
		sps.pred[v] = NULL;
	}
	sps.dist[src] = 0;

	// initialise priority queue
	PQ vertices = PQNew();
	for (Vertex v = 0; v < sps.numNodes; v++) {
		PQInsert(vertices, v, sps.dist[v]);
	}
	
	// relaxaion
	while(!PQIsEmpty(vertices)) {
		Vertex closest = PQDequeue(vertices);
		if (sps.dist[closest] != INFINITY) {
			AdjList adjs = GraphOutIncident(g, closest);
			for (AdjList adj = adjs; adj != NULL; adj = adj->next) {
				int relax = sps.dist[closest] + adj->weight;
				if (relax < sps.dist[adj->v]) {
					sps.dist[adj->v] = relax;
					PQUpdate(vertices, adj->v, relax);
					PredListFree(sps.pred[adj->v]);
					sps.pred[adj->v] = NULL;
					sps.pred[adj->v] = PredListAppend(sps.pred[adj->v], closest);
				} else if (relax == sps.dist[adj->v]) {
					PredListAppend(sps.pred[adj->v], closest);
				}
			}
		}
	}

	PQFree(vertices);
	return sps;
}

void showShortestPaths(ShortestPaths sps) {
	printf("Node %d\n  Distance\n", sps.src);
	for (Vertex v = 0; v < sps.numNodes; v++) {
		printf("    %d : ", v);
		if (sps.dist[v] == INFINITY) {
			printf("X\n");
		} else {
			printf("%d", sps.dist[v]);
		}
	}

	printf("  Preds\n");
	for (Vertex v = 0; v < sps.numNodes; v++) {
		printf("    %d : ", v);
		for (PredNode* curr = sps.pred[v]; curr != NULL; curr = curr->next) {
			printf("[%d]->", curr->v);
		}
		printf("NULL\n");
	}
}

void freeShortestPaths(ShortestPaths sps) {
	free(sps.dist);
	for (Vertex v = 0; v < sps.numNodes; v++) {
		PredListFree(sps.pred[v]);
	}
	free(sps.pred);
}



// Helper functions

// Generate a new pred node
static PredNode* PredNodeNew(Vertex v) {
	PredNode* new = malloc(sizeof(PredNode));
	new->v = v;
	new->next = NULL;
	return new;
}

// Append vertex v to pred list
static PredNode* PredListAppend(PredNode* head, Vertex v) {
	if (head == NULL) {
		return PredNodeNew(v);
	}
	PredNode* curr = head;
	while (curr->next != NULL) curr = curr->next;
	curr->next = PredNodeNew(v);
	return head;
}

// free a pred list
static void PredListFree(PredNode* head) {
	PredNode* tmp = NULL;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
