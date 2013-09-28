#include "Graph.h"

#include "Edge.h"
#include "Vertex.h"

#include <vector>
#include <limits>

#include "../Heap.h"
#include "../Node.h"
#include "../fibonacci/FibonacciHeap.h"
#include "../binary/BinaryHeap.h"


using namespace std;

GraphSource makeBuddeGraph(int size){
  GraphSource result;
  Graph* g = new Graph();

  Vertex* source = new Vertex(0);
  g->addVertex(source);
  
  Vertex* end = new Vertex(size+1);
  g->addVertex(end);

  for (int i = 1; i <= size ; i++){
    Vertex* temp  = new Vertex(i);    
    g->addVertex(temp);
    g->connectVertices(source,temp,i);
    g->connectVertices(temp,end,1);  
  }

  result.graph = g;
  result.source = source;
  return result;
}



void Graph::makePlot(string filename){
  ofstream file;
  string fname = filename+".gv";
  file.open(fname.c_str());
  file << "digraph G {\n";

  for( auto vertex : vertices ) {
    for ( auto edge : vertex->edges_ ) {
      file << vertex->id_ << " -> " << edge->n_->id_ << "[label=" << edge->d_ << "];" << endl;
    }
  }

  file << "}\n" << endl;
  file.close();
  string arg = "dot -Tps " + filename + ".gv -o "+ filename +".ps";
  system(arg.c_str());
}

void Graph::addVertex(Vertex* v){
	vertices.push_back(v);
}

void Graph::connectVertices(Vertex* from, Vertex* to, int distance){
	from->addNeighbour(to,distance);
}

void Graph::dijkstra(Vertex* source, Heap<Vertex*>* heap){
  countDecreaseKey = 0;
	for ( auto val : vertices){
		val->distanceFromStart_ = numeric_limits<int>::max(); 
		val->previous_ = NULL;
		val->node = NULL;
	}	
	
	source->distanceFromStart_ = 0;
	// here we need our queue.
	Heap<Vertex*> *Q = heap;
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
        countDecreaseKey++;
			}
		}	
	}
}
