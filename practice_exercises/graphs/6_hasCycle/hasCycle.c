
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

static bool dfsCycleCheck(Graph g, int nV, int curr, int *visited);

bool hasCycle(Graph g) {
	bool result = false;
    int nV = GraphNumVertices(g);
    int *visited = malloc(nV * sizeof(int));
    for (int src = 0; src < nV; src++) {
        for (int i = 0; i < nV; i++) {
            visited[i] = -1;
        }
        visited[src] = src;
        if (dfsCycleCheck(g, nV, src, visited)) {
            result = true;
            break;
        }
    }
    free(visited);
    return result;
}

static bool dfsCycleCheck(Graph g, int nV, int curr, int *visited) {
    for (int i = 0; i < nV; i++) {
        if (GraphIsAdjacent(g, curr, i)) {
            if (visited[i] == -1) {
                visited[i] = curr;
                if (dfsCycleCheck(g, nV, i, visited)) return true;
            } else {
                if (i != visited[curr]) return true;
            }
        }
    }
    return false;
}