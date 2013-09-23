#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
//#include "test/TestPerformance.h"
//#include "binary/BinaryHeap.h"
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

void testFib() {
  TestFibHeap *test = new TestFibHeap();
  assert(test->testFib());
}

int main(int argc, char* argv[]) {
    //dijkstra();
  testFib();
}
