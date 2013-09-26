#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "Edge.h"
#include "Vertex.h"

using namespace std;

class Graph {
 public:
  vector<Vertex*> vertices;
  void addVertex(Vertex* v);
  void connectVertices(Vertex* from, Vertex* to, int distance);
  void dijkstra(Vertex* source);
};

#endif
