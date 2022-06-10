// Centrality Measures ADT interface
// COMP2521 Assignment 2

// Note: You MUST NOT modify this file.

#ifndef CENTRALITY_MEASURES_H
#define CENTRALITY_MEASURES_H

#include <stdbool.h>

#include "Graph.h"

typedef struct NodeValues {
	int numNodes;   // The number of nodes in the graph
	double *values; // An  array  of  values, one  for  each vertex. The
	                // meaning of the values depends on  which  function
	                // is being called.
} NodeValues;


/**
 * Finds the closeness centrality for each vertex in the given graph and
 * returns the results in a NodeValues structure.
 */
NodeValues closenessCentrality(Graph g);

/**
 * Finds  the  betweenness centrality for each vertex in the given graph
 * and returns the results in a NodeValues structure.
 */
NodeValues betweennessCentrality(Graph g);

/**
 * Finds  the  normalised  betweenness centrality for each vertex in the
 * given graph and returns the results in a NodeValues structure.
 */
NodeValues betweennessCentralityNormalised(Graph g);

/**
 * This  function is for you to print out the NodeValues structure while
 * you are debugging/testing your implementation. 
 * 
 * We  will  not call this function during testing, so you may print out
 * the given NodeValues structure in whatever format you want.
 */
void showNodeValues(NodeValues nvs);

/**
 * Frees all memory associated with the given NodeValues structure.
 */
void freeNodeValues(NodeValues nvs);

#endif

