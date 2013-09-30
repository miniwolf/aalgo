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
  GraphSource* gs = makeBuddeGraph(size);
  double* temp = testDijkstra(gs);
  delete gs->graph;
  delete gs;
  return temp;
}

double* TestPerformance::testDijkstraLukas(int size){
  GraphSource* gs = makeLukasGraph(size);
  double* temp = testDijkstra(gs);
  delete gs->graph;
  delete gs;
  return temp;
}

double* TestPerformance::testDijkstraNtagram(int size){
  GraphSource* gs = makeNtagramGraph(size);
  double* tmp = testDijkstra(gs);
  delete gs->graph;
  delete gs;
  return tmp;
}

void TestPerformance::testNTagramDijkstra(int size, ofstream & file){
    GraphSource* gs = makeNtagramGraph(size);

    double* results = testDijkstra(gs);
    int decreaseCalls = gs->graph->countDecreaseKey;

    file << size << ", " << decreaseCalls << ", " << results[0] << ", " << results[1] << ", " << endl;
    delete []results;
    delete gs->graph;
    delete gs;
}

double* TestPerformance::testDijkstra(GraphSource* gs){
  double* result = new double[2];
  Heap<Vertex*>* fheap = new FibonacciHeap<Vertex*>();

  startClock();
  gs->graph->dijkstra(gs->source,fheap);
  result[0] = stopClock();

  cout << "Fibonacci - decrease key calls: " << gs->graph->countDecreaseKey << " Time: " << result[0] << endl;

  Heap<Vertex*>* bheap = new BinaryHeap<Vertex*>();
  startClock();
  gs->graph->dijkstra(gs->source, bheap);
  result[1] = stopClock();
  cout << " Binary - decrease key calls: " << gs->graph->countDecreaseKey <<  " Time: " << result[1] <<endl;
  delete fheap;
  delete bheap;
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
