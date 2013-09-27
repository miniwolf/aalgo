#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "test/TestPerformance.h"
#include "binary/BinaryHeap.h"
#include "dijkstra/Vertex.h"
#include "dijkstra/Graph.h"
#include "test/TestFibHeap.h"

using namespace std;

string IntToString(int num) {
  ostringstream myStream;
  myStream << num << flush;
  return myStream.str();
}

void dijkstra() {
  Vertex* n1 = new Vertex(1);
  Vertex* n2 = new Vertex(2);

  n1->addNeighbour(n2,10);

  Graph* g = new Graph();
  g->addVertex(n1);
  g->addVertex(n2);
  g->dijkstra(n1);
}

void testPerformance(){
  TestPerformance* tPerf = new TestPerformance();
  ofstream ffile, bfile;
  string ffilename = "test_f_file", bfilename = "test_b_file";
  ffile.open(ffilename.c_str());
  bfile.open(bfilename.c_str());
  for(int size = 1000; size<=10000000; size = size*10){
    for(int i = 0; i<50; i++){
      cout << size << endl;
      Heap<int>* bHeap = new BinaryHeap<int>();
      Heap<int>* fHeap = new FibonacciHeap<int>();
      int* set = new int[size];
      tPerf->generateKeySet(size, set);
      ffile << size << ", ";
      bfile << size << ", ";
      tPerf->runTest(fHeap, size, set, ffile);
      tPerf->runTest(bHeap, size, set, bfile);
      ffile << endl;
      bfile << endl;
      ffile.flush();
      bfile.flush();
      delete []set;
      delete fHeap;
      //delete bHeap;
    }
    
  }
  ffile.close();
  bfile.close();
  
}

void testFib() {
  TestFibHeap *test = new TestFibHeap();
  assert(test->testFib());
}

int main(int argc, char* argv[]) {
  testPerformance();
}
