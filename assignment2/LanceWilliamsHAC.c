// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"

#define INFINITY 2

static void freeDist(double **dist, int n);
static double getDist(Graph g, Vertex i, Vertex j);
static double getWeight(AdjList l, Vertex v);
static double maximum(double a, double b);
static double minimum(double a, double b);
static Dendrogram newDNode(int Vertex);


/**
 * Generates  a Dendrogram using the Lance-Williams algorithm (discussed
 * in the spec) for the given graph  g  and  the  specified  method  for
 * agglomerative  clustering. The method can be either SINGLE_LINKAGE or
 * COMPLETE_LINKAGE (you only need to implement these two methods).
 * 
 * The function returns a 'Dendrogram' structure.
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    int n = GraphNumVertices(g);
    // initailise dist[][]
    double **dist = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        dist[i] = malloc(n * sizeof(double));
    }
    // calculate dist
    for (Vertex i = 0; i < n; i++) {
        for (Vertex j = 0; j < i; j++) {
            dist[i][j] = dist[j][i] = getDist(g, i, j);  
        }
    }
    // initialise dendA
    Dendrogram *dendA = malloc(n * sizeof(Dendrogram));
    for (int i = 0; i < n; i++) {
        dendA[i] = newDNode(i);
    }
    int dendIndex = 0;
    // update dendrograms
    for (int size = n; size > 1; size--) {
        // find index of min value
        double min = INFINITY;
        int minI = 0;
        int minJ = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (dist[i][j] < min) {
                    min = dist[i][j];
                    minI = i;
                    minJ = j;
                }
            }
        }
        // merge minI into minJ
        if (method == SINGLE_LINKAGE) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if (i == minI || j == minI) {
                        continue;
                    }
                    if (i == minJ) {
                        dist[i][j] = dist[j][i] = minimum(dist[minJ][j], dist[minI][j]);
                    }
                    if (j == minJ) {
                        dist[i][j] = dist[j][i] = minimum(dist[i][minJ], dist[i][minI]);
                    }
                }
            }            
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if (i == minI || j == minI) {
                        continue;
                    }
                    if (i == minJ) {
                        dist[i][j] = dist[j][i] = maximum(dist[minJ][j], dist[minI][j]);
                    }
                    if (j == minJ) {
                        dist[i][j] = dist[j][i] = maximum(dist[i][minJ], dist[i][minI]);
                    }
                }
            }       
        }
        // clear minI
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (i == minI || j == minI) {
                    dist[i][j] = dist[j][i] = INFINITY;
                }
            }
        }
        Dendrogram temp = dendA[minJ];
        dendA[minJ] = newDNode(-1);
        dendA[minJ]->left = temp;
        dendA[minJ]->right = dendA[minI];
        dendA[minI] = NULL;
        dendIndex = minJ;
    }
    Dendrogram final = dendA[dendIndex];
    freeDist(dist, n);
    free(dendA);
    return final;
}

/**
 * Frees all memory associated with the given Dendrogram structure.
 */
void freeDendrogram(Dendrogram d) {
    if (d != NULL) {
        freeDendrogram(d->left);
        freeDendrogram(d->right);
        free(d);
    }
}



// helper functions

// free distance lists
static void freeDist(double **dist, int n) {
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
}

// get distance between two vertex
static double getDist(Graph g, Vertex i, Vertex j) {
    if (GraphIsAdjacent(g, i, j) && GraphIsAdjacent(g, j, i)) {
        double distij = getWeight(GraphOutIncident(g, i), j);
        double distji = getWeight(GraphInIncident(g, i), j);
        return 1/maximum(distij, distji);
    } else {
        if (GraphIsAdjacent(g, i, j)) {
            return 1/getWeight(GraphOutIncident(g, i), j);
        } else if (GraphIsAdjacent(g, j, i)) {
            return 1/getWeight(GraphInIncident(g, i), j);
        } else {
            return INFINITY;
        }
    }
}

// get weight of a given vertex from a adjlist
static double getWeight(AdjList l, Vertex v) {
    for (AdjList curr = l; curr != NULL; curr = curr->next) {
        if (curr->v == v) {
            return curr->weight;
        }
    }
    return INFINITY;
}

// take the larger one 
static double maximum(double a, double b) {
    return a > b ? a : b;
}

// take the less one
static double minimum(double a, double b) {
    return a < b ? a : b;
}

// create a new DNode
static Dendrogram newDNode(int Vertex) {
    Dendrogram new = malloc(sizeof(DNode));
    new->vertex = Vertex;
    new->left = NULL;
    new->right = NULL;
    return new;
}
