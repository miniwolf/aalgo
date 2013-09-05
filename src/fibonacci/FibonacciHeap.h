#ifndef FIBONACCI_HEAP_H_
#define FIBONACCI_HEAP_H_

#include "FNode.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class FibonacciHeap {
 public:
  FNode *minRoot;
  int size;

  FibonacciHeap(){
    minRoot=NULL;
    size=0;
  }
  FNode* insert(int key, string payload);
  void meld(FibonacciHeap *other);
  FNode* findMin();
  FNode* deleteMin();
  void decreaseKey(FNode *node, int key);
  void remove(FNode *node);
  void insertNode(FNode *node);
  void makeplot(string filename);
};

#endif
