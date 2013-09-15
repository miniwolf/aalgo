#include "Graph.h"

#include "Edge.h"
#include "Vertex.h"

#include <vector>
#include <limits>

#include "../Heap.h"
#include "../Node.h"
#include "../fibonacci/FibonacciHeap.h"

using namespace std;

void Graph::addVertex(Vertex* v){
	vertices.push_back(v);
}

void Graph::connectVertices(Vertex* from, Vertex* to, int distance){
	from->addNeighbour(to,distance);
}

void Graph::dijkstra(Vertex* source){
	for ( auto val : vertices){
		val->distanceFromStart_ = numeric_limits<int>::max(); 
		val->previous_ = NULL;
		val->node = NULL;
	}	
	
	source->distanceFromStart_ = 0;
	// here we need or queue.0
	Heap<Vertex*> *h = new FibonacciHeap<Vertex*>();
	for ( auto val : vertices){
		int d = val->distanceFromStart_;
		Node<Vertex*>* n = h->insert(d,val);
	}
	
}
