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
	// here we need our queue.
	Heap<Vertex*> *Q = new FibonacciHeap<Vertex*>();
	for ( auto val : vertices){
		int d = val->distanceFromStart_;
		Node<Vertex*>* n = Q->insert(d,val);
		val->node = n;
	}

	while(Q->findMin() != NULL){
		Node<Vertex*>* uNode = Q->deleteMin();
		Vertex* u = uNode->payload;
		
		if ( u->distanceFromStart_ == numeric_limits<int>::max() ){
			break;
		}

		for ( auto val : u->edges_ ) {
			Vertex* v = val->n_;
			int distanceFromUtoV = val->d_;
			int alt = u->distanceFromStart_ + distanceFromUtoV;

			if ( alt < v->distanceFromStart_ ){
				v->distanceFromStart_ = alt;
				v->previous_ = u;
				Q->decreaseKey(v->node,v->distanceFromStart_);
			}
		}	
	}
}
