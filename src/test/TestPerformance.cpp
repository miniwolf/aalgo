#include "TestPerformance.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "../dijkstra/Graph.h"
using namespace std;

int* TestPerformance::generateKeySet(int i, int* ar ){
  srand(time(NULL));
  for(int j = 0; j < i; j++){
    ar[j] = rand();
  }
  return ar;
}

Node<int>** TestPerformance::testInsert(Heap<int>* heap, int* set, int size, Node<int>** array){
  for(int i = 0;  i< size; i++){
    array[i] = heap->insert(set[i], set[i]);
  }
  return array;
}

void TestPerformance::testDeleteMin(Heap<int>* heap){
  Node<int>* n = NULL;
    while(heap->findMin()){
    n = heap->deleteMin();
    if(n){ delete n; }
  };
}


void TestPerformance::testDecreaseKey(Heap<int>* heap, Node<int>** array, int size ){
  for(int i = 0; i < size; i++){
    heap->decreaseKey(array[i], (array[i]->key)/2 );
  }
}

void TestPerformance::startClock(){
  mStartTime = getTime();
}

double TestPerformance::stopClock(){

  return (getTime()) - mStartTime;
}

double TestPerformance::getTime(){
  timeval tv;
  gettimeofday (&tv, NULL);
  return double (tv.tv_sec) + 0.000001 * tv.tv_usec;
}

double* TestPerformance::testDijkstraBudde(int size){
  GraphSource gs = makeBuddeGraph(size);
  double* temp = testDijkstra(gs);
  delete gs.graph;
  return temp;
}

double* TestPerformance::testDijkstraLukas(int size){
  GraphSource gs = makeLukasGraph(size);
  double* temp = testDijkstra(gs);
  delete gs.graph;
  return temp;
}

double* TestPerformance::testDijkstraNtagram(int size){
  GraphSource gs = makeNtagramGraph(size);
  double* tmp = testDijkstra(gs);
  delete gs.graph;
  return tmp;

}

double* TestPerformance::testDijkstra(GraphSource gs){
  double* result = new double[2];

  startClock();
  gs.graph->dijkstra(gs.source,new FibonacciHeap<Vertex*>());
  result[0] = stopClock();

  startClock();
  gs.graph->dijkstra(gs.source, new BinaryHeap<Vertex*>());
  result[1] = stopClock();
  cout << " decrease key calls: " << gs.graph->countDecreaseKey << endl;
  return result;
}

void TestPerformance::runTest(Heap<int>* heap, int size, int* set, ofstream & file){
  Node<int>** nodes = new Node<int>*[size];
  startClock();
  testInsert(heap, set, size, nodes);
  file << stopClock() << ", " ;
  Node<int>* n = heap->insert(500,500);
  heap->remove(n);

  startClock();
  testDecreaseKey(heap, nodes, size);
  file << stopClock() << ", ";

  startClock();
  testDeleteMin(heap);
  file << stopClock()  << ", ";

  delete []nodes;
}
