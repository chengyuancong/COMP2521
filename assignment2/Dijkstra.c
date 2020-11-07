// Dijkstra ADT implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "PQ.h"

#define INFINITY 2147483647

typedef PredNode* PredList;

static PredList freePredList(PredList head);
static PredList predListAppend(PredList head, Vertex v);
static PredList newPredNode(Vertex v);

ShortestPaths dijkstra(Graph g, Vertex src) {
	int nV = GraphNumVertices(g);
	// initialise sps
	ShortestPaths sps;
	sps.numNodes = nV;
	sps.src = src;
	sps.dist = malloc(nV * sizeof(int));
	sps.pred = malloc(nV * sizeof(PredList));
	for (int i = 0; i < nV; i++) {
		sps.dist[i] = INFINITY;
		sps.pred[i] = NULL;
	}
	sps.dist[src] = 0;
	// initialise priority queue
	PQ vSet = PQNew();
	for (int i = 0; i < nV; i++) {
		PQInsert(vSet, i, sps.dist[i]);
	}
	// relaxaion
	while (!PQIsEmpty(vSet)) {
		Vertex min = PQDequeue(vSet);
		AdjList minOut = GraphOutIncident(g, min);
		for (AdjList curr = minOut; curr != NULL; curr = curr->next) {
			if (sps.dist[min] + curr->weight < sps.dist[curr->v] && sps.dist[min] != INFINITY) {
				sps.dist[curr->v] = sps.dist[min] + curr->weight;
				PQUpdate(vSet, curr->v, sps.dist[curr->v]);
				sps.pred[curr->v] = freePredList(sps.pred[curr->v]);
				sps.pred[curr->v] = predListAppend(sps.pred[curr->v], min);
			} else if (sps.dist[min] + curr->weight == sps.dist[curr->v] && sps.dist[min] != INFINITY) {
				sps.pred[curr->v] = predListAppend(sps.pred[curr->v], min);
			}
		}
	}
	// set infinity dist to 0
	for (int i = 0; i < nV; i++) {
		if (sps.dist[i] == INFINITY) {
			sps.dist[i] = 0;
		}		
	}
	return sps;
}

void showShortestPaths(ShortestPaths sps) {
	int i = 0;
	printf("Node %d\n", sps.src);
	printf("  Distance\n");
	for (i = 0; i < sps.numNodes; i++) {
		if (i == sps.src)
			printf("    %d : X\n", i);
		else
			printf("    %d : %d\n", i, sps.dist[i]);
	}
	
	printf("  Preds\n");
	for (i = 0; i < sps.numNodes; i++) {
		int numPreds = 0;
		int preds[sps.numNodes];
		printf("    %d : ",i);
		PredNode *curr = sps.pred[i];
		while (curr != NULL && numPreds < sps.numNodes) {
			preds[numPreds++] = curr->v;
			curr = curr->next;
		}
		
		// Insertion sort
		for (int j = 1; j < numPreds; j++) {
			int temp = preds[j];
			int k = j;
			while (k > 0 && preds[k - 1] > temp) {
				preds[k] = preds[k - 1];
				k--;
			}
			preds[k] = temp;
		}
		
		for (int j = 0; j < numPreds; j++) {
			printf("[%d]->", preds[j]);
		}
		printf("NULL\n");
	}
}

void freeShortestPaths(ShortestPaths sps) {
	free(sps.dist);
	for (int i = 0; i < sps.numNodes; i++) {
		sps.pred[i] = freePredList(sps.pred[i]);
	}
	free(sps.pred);
}

// Helper functions
static PredList freePredList(PredList head) {
	while (head != NULL) {
		PredList temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}

static PredList predListAppend(PredList head, Vertex v) {
	if (head == NULL) {
		return newPredNode(v);
	}
	head->next = predListAppend(head->next, v);
	return head;
}

static PredList newPredNode(Vertex v) {
	PredList new = malloc(sizeof(PredNode));
	new->v = v;
	new->next = NULL;
	return new;
}