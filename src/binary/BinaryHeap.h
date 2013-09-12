#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include "../Heap.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std 

class BinaryHeap : public Heap{
  virtual BNode* insert(int key, string payload){}
  virutal BNode* findMin(){}
  virtual BNode* deleteMin(){}

  virtual void decreaseKey(Node* node, int key){
  }

  virtual void decreaseKey(BNode* node, int key){
  }
  
  virtual void makePlot(string filename){

  }

};

#endif
