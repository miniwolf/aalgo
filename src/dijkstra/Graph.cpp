#include "Graph.h"

#include "Edge.h"
#include "Vertex.h"

#include <vector>
#include <limits>
#include <cstdlib>


#include "../Heap.h"
#include "../Node.h"
#include "../fibonacci/FibonacciHeap.h"
#include "../binary/BinaryHeap.h"


using namespace std;
// building high density graphs is SLOW :/
template <class T>
void shuffle(T* array, int size){
    srand(time(NULL));
    for ( int i = size-1 ; i > 0 ; i--){
        int j = rand() % (i+1);
        assert( 0 <= j && j <= i);
        T temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

GraphSource* makeRandomGraph(int size, int density){
    assert(density < size - 1);
    srand(time(NULL));
    GraphSource* result = new GraphSource();
    Graph* g = new Graph();

    Vertex** vArray = new Vertex*[size];
    Vertex** shuffleArray = new Vertex*[size];
    for( int i = 0 ; i < size ; i++){
        vArray[i] = new Vertex(i);
        shuffleArray[i] = vArray[i];
        g->addVertex(vArray[i]);
    }

    for ( int i = 0; i < size ; i++){
        Vertex* v = vArray[i];
        int dense = 0;

        shuffle(shuffleArray,size);
        int sIndex = 0;
        while( dense < density){
            assert(sIndex < size);
            Vertex* u = shuffleArray[sIndex];
            if(v!=u){
                v->addNeighbour(u,rand()%100000);
                dense++;
            }
            sIndex++;
        }
    }

    result->graph = g;
    result->source = vArray[0];
    delete []vArray;
    return result;
}

GraphSource* makeNtagramGraph(int size){
  GraphSource* result = new GraphSource();
  Graph* g = new Graph();

  Vertex* source = new Vertex(0);
  g->addVertex(source);
  Vertex** vArray = new Vertex*[size];
  vArray[0] = source;
  for (int i = 1; i < size ; i++){
    Vertex* temp  = new Vertex(i);
    g->addVertex(temp);
    vArray[i] = temp;
  }

  for(int i = 0; i < size-1 ; i++){
    Vertex* next = vArray[i+1];
    Vertex* current = vArray[i];
    g->connectVertices(current, next, 1);
    for(int j = i+2; j < size; j++){
      g->connectVertices(current, vArray[j], 2*size+1-2*i);
    }
  }

  result->graph = g;
  result->source = source;
  return result;
}



GraphSource* makeBuddeGraph(int size){
  GraphSource* result = new GraphSource();
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

  result->graph = g;
  result->source = source;
  return result;
}

GraphSource* makeLukasGraph(int size){
  GraphSource* result = new GraphSource();
  Graph* g = new Graph();

  Vertex* source = new Vertex(0);
  g->addVertex(source);

  Vertex* end = new Vertex(size+1);
  g->addVertex(end);

  for (int i = 1; i <= size ; i++){
    Vertex* temp  = new Vertex(i);
    g->addVertex(temp);
    g->connectVertices(source,temp,i);
    g->connectVertices(temp,end,size*2 +1 - i*2);
  }

  result->graph = g;
  result->source = source;
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
   // cout << "Inserting " << d << " " << val->id_ << endl;
    val->node = n;
  }

  while(Q->findMin() != NULL){
    Node<Vertex*>* uNode = Q->deleteMin();
    Vertex* u = uNode->payload;
    //cout << "Deleting " << uNode->key << " " << u->id_ << endl ;
    delete uNode;

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
	//cout << "Decrease Key " <<  v->id_ << " to: " << v->distanceFromStart_ << endl ;
	countDecreaseKey++;
      }
    }
  }
}
