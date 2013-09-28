#ifndef TESTPERFORMANCE_H
#define TESTPERFORMANCE_H

#include "../Heap.h"
#include "../binary/BinaryHeap.h"
#include "../fibonacci/FibonacciHeap.h"
#include "../dijkstra/Graph.h"

class TestPerformance {
 private:
  long double mStartTime;
  double getTime();
 public:
  TestPerformance(){
    mStartTime = 0;
  }
  int* generateKeySet(int i, int* ar);
  Node<int>** testInsert(Heap<int>* heap, int* set, int size, Node<int>** array);
  void testDeleteMin(Heap<int>* heap);
  void testDecreaseKey(Heap<int>* heap, Node<int>** array, int size );
  void runTest(Heap<int>* heap, int size, int* set, ofstream &file); 
  void startClock();
  double stopClock();

  double* testDijkstraBudde(int size);
  double* testDijkstraLukas(int size);
  double* testDijkstraNtagram(int size);
  double* testDijkstra(GraphSource gs);  
};

#endif
