#ifndef VERTEX_H_
#define VERTEX_H_

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "Edge.h"
#include "../Node.h"

using namespace std;


class Vertex {
  public:
	Node<Vertex*> *node;
	int id_;
	Vertex* previous_;
	int distanceFromStart_;
	vector<Edge*> edges_;
	void addNeighbour(Vertex* vertex, int d);

	Vertex(int id);	
};

#endif
