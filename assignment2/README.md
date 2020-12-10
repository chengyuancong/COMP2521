# Assignment 2 - Social Network Analysis  
In this assignment, your task is to implement graph based data analysis functions (ADTs) to mine a given social network. For example, detect say "influenciers", "followers", "communities", etc. in a given social network. The main focus of this assignment is to calculate measures that could identify say "influenciers", "followers", etc., and also discover possible "communities" in a given social network.  

### Part-1: Dijkstra's algorithm  
In order to discover say "influencers", we need to repeatedly find shortest paths between all pairs of nodes. In this section, you need to implement Dijkstra's algorithm to discover shortest paths from a given source to all other nodes in the graph. The function offers one important additional feature, the function keeps track of multiple predecessors for a node on shortest paths from the source, if they exist. The function returns 'ShortestPaths' structure with the required information (i.e. 'distance' array, 'predecessor' arrays, source and no_of_nodes in the graph).

### Part-2: Centrality Measures for Social Network Analysis
Centrality measures play very important role in analysing a social network. For example, nodes with higher "betweenness" measure often correspond to "influencers" in the given social network. In this part you will implement two well known centrality measures for a given directed weighted graph.

### Part-3: Discovering Community
In this part you need to implement the Hierarchical Agglomerative Clustering (HAC) algorithm to discover communities in a given graph. In particular, you need to implement Lance-Williams algorithm.

## Test Summary
```
!!perftab       ** PERFORMANCE ANALYSIS **

Test  1 (1)     testDijkstra graphs/2.in ..  ..  ..  ..  ..  !!PASSed
Test  2 (1)     testDijkstra graphs/4.in ..  ..  ..  ..  ..  !!PASSed
Test  3 (1)     testDijkstra graphs/7.in ..  ..  ..  ..  ..  !!PASSed
Test  4 (1)     testDijkstra graphs/8.in ..  ..  ..  ..  ..  !!PASSed
Test  5 (0.75)  testCentralityMeasures graphs/2.in "c"   ..  !!PASSed
Test  6 (0.75)  testCentralityMeasures graphs/6.in "c"   ..  !!PASSed
Test  7 (0.75)  testCentralityMeasures graphs/7.in "c"   ..  !!PASSed
Test  8 (0.75)  testCentralityMeasures graphs/8.in "c"   ..  !!PASSed
Test  9 (0.75)  testCentralityMeasures graphs/5.in "b"   ..  !!PASSed
Test 10 (0.75)  testCentralityMeasures graphs/6.in "b"   ..  !!PASSed
Test 11 (0.75)  testCentralityMeasures graphs/7.in "b"   ..  !!PASSed
Test 12 (0.75)  testCentralityMeasures graphs/8.in "b"   ..  !!PASSed
Test 13 (0.75)  testCentralityMeasures graphs/9.in "c"   ..  !!PASSed
Test 14 (0.75)  testCentralityMeasures graphs/10.in "c"  ..  !!PASSed
Test 15 (0.75)  testCentralityMeasures graphs/9.in "b"   ..  !!PASSed
Test 16 (0.75)  testCentralityMeasures graphs/10.in "b"  ..  !!PASSed
Test 17 (0.75)  known graph  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 18 (0.75)  unknwon graph    ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 19 (0.75)  unknwon graph    ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 20 (0.75)  unknwon graph    ..  ..  ..  ..  ..  ..  ..  !!PASSed

!!perfmark      ** TOTAL PERFORMANCE MARK:    16/16

!!marktab       **  MARKER'S  ASSESSMENT  **

             Style, Complexity, Comments  (4)   4
 ^
 + =========================================================== +
 + Well done! The code is structured well and has good         +
 + comments. I would like to see more explaination throughout  +
 + but the current comments are serviceable. Keep up the good  +
 + work.                                                       +
 + =========================================================== +

!!finalmark     **  FINAL  ASSIGNMENT  MARK:    20/20

5285978 Cheng, Yuancong                         3707/2 COMPBH




Marked by z5230768 on Wed Dec  9 12:27:34 2020
```