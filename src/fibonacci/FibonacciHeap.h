#include "FNode.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class FibonacciHeap {
 public:
  FNode *minRoot;
  int size;

  FibonacciHeap(){
    size = 0;
  }
  FNode* insert(int key, string payload);
  void meld(FibonacciHeap *other);
  FNode* findMin();
  FNode* deleteMin();

};
