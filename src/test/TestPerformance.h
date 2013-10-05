#ifndef TESTPERFORMANCE_H
#define TESTPERFORMANCE_H

#include "../Heap.h"
#include "../binary/BinaryHeap.h"
#include "../fibonacci/FibonacciHeap.h"
#include "../dijkstra/Graph.h"
#include "../timespec/timespec.h"

class TestPerformance {
 private:
  timespec mStartTime;
  void getTime();
 public:
  TestPerformance(){  }
  int* generateKeySet(int i, int* ar);
  Node<int>** testInsert(Heap<int>* heap, int* set, int size, Node<int>** array);
  void testDeleteMin(Heap<int>* heap);
  void testDecreaseKey(Heap<int>* heap, Node<int>** array, int size );

  Node<int>** testWorstInsert(Heap<int>* heap, int size, Node<int>** array);
  void testWorstDecreaseKey(Heap<int>* heap, Node<int>** array, int size );
  void performWorstTest(Heap<int>* heap, int size, ofstream &file);

  void runTest(Heap<int>* heap, int size, int* set, ofstream &file);
  void startClock();
  void testNTagramDijkstra(int size, ofstream & file);
  void performLayerInsert(Heap<int>* heap,int layer, ofstream & file);

  void testSameSizeInsertions(Heap<int>* heap, int size, int averageFactor, ofstream & file);

  double testRandomGraphDecreaseKey(int size, int density, int average, ofstream & file);
  double stopClock();

  void performRandomGraph(int size, int density,int average, ofstream & binary, ofstream & fib , ofstream & decrease);

  double* testDijkstraBudde(int size);
  double* testDijkstraLukas(int size);
  double* testDijkstraNtagram(int size);
  double* testDijkstra(GraphSource* gs);
};

#endif
