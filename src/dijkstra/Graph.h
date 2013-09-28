#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string>
#include "Edge.h"
#include "Vertex.h"
#include "../Heap.h"

using namespace std;

class Graph {
 public:
  vector<Vertex*> vertices;
  int countDecreaseKey;
  void addVertex(Vertex* v);
  void connectVertices(Vertex* from, Vertex* to, int distance);
  void dijkstra(Vertex* source, Heap<Vertex*>* heap);
  void makePlot(string filename);
};

struct GraphSource{
  Graph* graph = NULL;
  Vertex* source = NULL;
};

GraphSource makeBuddeGraph(int size);

#endif
