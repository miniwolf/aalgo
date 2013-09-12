#ifndef HEAP_H_
#define HEAP_H_
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
using namespace std;

class Heap{
 public:
  virtual Node* insert(int key, string payload)  = 0;
  virtual Node* findMin() = 0;
  virtual Node* deleteMin() = 0;
  virtual void decreaseKey(Node* node, int key) = 0;
  virtual void makePlot(string filename) = 0;
  
};


#endif
