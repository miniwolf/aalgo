#include "TestPerformance.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "../dijkstra/Graph.h"
#include <cmath>
#include <time.h>

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

Node<int>** TestPerformance::testWorstInsert(Heap<int>* heap, int size, Node<int>** array){
  for(int i = 0;  i< size; i++){
    array[i] = heap->insert(2*size - i, 2*size - i);
  }
  return array;
}

void TestPerformance::testWorstDecreaseKey(Heap<int>* heap, Node<int>** array, int size ){
  for(int i = 0; i < size; i++){
    heap->decreaseKey(array[i], size-i);
  }
}

void TestPerformance::startClock(){
  getTime();
}

double TestPerformance::stopClock(){
  timespec currentTime;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &currentTime);

  timespec result = timespec_sub(currentTime, mStartTime);

  return double(result.tv_sec) + 0.000000001*double(result.tv_nsec);
}

void TestPerformance::getTime(){
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mStartTime);
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

double TestPerformance::testRandomGraphDecreaseKey(int size, int density, int average, ofstream & file){
    int temp = 0;
    double time = 0.0;
    for(int i = 0; i < average; i++){
        GraphSource* gs = makeRandomGraph(size,density);
        Heap<Vertex*>* heap = new BinaryHeap<Vertex*>();

        startClock();
        gs->graph->dijkstra(gs->source, heap);
        time+=stopClock();
        temp+=gs->graph->countDecreaseKey;
        delete gs->graph;
        delete gs;
        delete heap;
    }
    temp = temp/average;
    file << temp << ", ";

    return time/average;
}

void TestPerformance::testSameSizeInsertions(Heap<int>* heap, int heapsize, int averageFactor, ofstream & file){
   int* keys = new int[heapsize];
   keys = generateKeySet(heapsize,keys);

   Node<int>** nodes = new Node<int>*[heapsize];
   nodes = testInsert(heap,keys,heapsize,nodes);

    for(int i = 0 ; i < averageFactor ; i++){
       // int r = rand();
        Node<int>* node = NULL;
        startClock();
        node = heap->insert(0,0);
        double time = stopClock();
        int comparisons = heap->getComparisons();
        heap->remove(node);
        file << heapsize << ", "<< time << ", " << comparisons << endl;
        delete node;
    }

    testDeleteMin(heap);


   delete [] keys;
   delete [] nodes;
}

void TestPerformance::runTest(Heap<int>* heap, int size, int* set, ofstream & file){
  Node<int>** nodes = new Node<int>*[size];

  //insert
  startClock();
  testInsert(heap, set, size, nodes);
  file << stopClock() << ", " ;
  //

  Node<int>* n = heap->insert(500,500);
  heap->remove(n);
  delete n;

  startClock();
  testDecreaseKey(heap, nodes, size);
  file << stopClock() << ", ";

  startClock();
  testDeleteMin(heap);
  file << stopClock()  << ", ";

  delete []nodes;
}

void TestPerformance::performWorstTest(Heap<int>* heap, int size, ofstream &file){
  Node<int>** nodes = new Node<int>*[size];

  //insert
  startClock();
  testWorstInsert(heap, size, nodes);
  file << stopClock() << ", " ;
  //

  Node<int>* n = heap->insert(500,500);
  heap->remove(n);
  delete n;

  startClock();
  testWorstDecreaseKey(heap, nodes, size);
  file << stopClock() << ", ";

  startClock();
  testDeleteMin(heap);
  file << stopClock()  << ", ";

  delete []nodes;
}


int myPow(int x, int p){
    if(p==0) return 1;
    if(p==1) return x;

    int tmp = myPow(x, p/2);
    if(p%2 == 0) return tmp*tmp;
    else return x*tmp*tmp;
}

void TestPerformance::performLayerInsert(Heap<int>* heap, int layer, ofstream & file){
    // build a full heap, with layer-1 layers. Layer 0 has one element, Layer 1 has two etc..
    int totalElements = 1;
    for(int i = 0; i < layer; i++ ){
        totalElements += myPow(2,i);
    }
    cout << totalElements << endl;

    // total elements is total elements +1.
    int total = 0;
    for(int i = 0; i < layer; i++ ){
    cout << "layer: " << i << endl;
        double totalTime = 0.0;

        int layerElements = myPow(2,i);
       // keys = generateKeySet(layerElements,keys);
        startClock();
        for(int j = 0; j < layerElements ; j++){
            // key is total-i, so this will be the smallest key yet!
            heap->insert(totalElements- total, totalElements - total);
            total++;
        }
        totalTime = stopClock();
        totalTime = totalTime/layerElements;
        // the average time for all the inserts on this layer.
        file << totalTime << ", ";
        file.flush();
       // delete []keys;
    }
    file << endl;
}

