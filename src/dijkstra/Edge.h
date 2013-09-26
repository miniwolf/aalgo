#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <limits.h>

using namespace std;

class Vertex;

class Edge {
 public:
	Vertex *n_;
	int d_;

	Edge(Vertex* v, int dist);
	~Edge();
};

#endif
