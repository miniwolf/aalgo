#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../Heap.h"
#include "BNode.h"

using namespace std;

class BinaryHeap : public Heap {
private:
  int size = 0;
  BNode* root = NULL;
public:
  BinaryHeap(){}
  virtual BNode* insert(int key, string payload) {
    size++;
    
    BNode* node = new BNode(key, payload);
    
    if ( size == 1 ) {
      root = node;
      return node;
    }
    
    size_t n = size, i = 0, arSize = (sizeof(size) + 1) * 8;
    bool boolAr[arSize];
    while ( n != 0 ) {
      i++;      
      boolAr[arSize-i] = (n % 2) == 1;
      n /= 2;
    }
    
    root->insert(node, boolAr, (arSize - i + 1));
    return node;
  }
  
  virtual BNode* findMin() {
    return root;
  }

  virtual BNode* deleteMin(){}
  virtual void decreaseKey(Node* node, int key){}
  virtual void decreaseKey(BNode* node, int key){}
};

#endif
