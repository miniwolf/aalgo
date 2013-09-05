#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include "BNode.h"

using namespace std; 

class BinomialHeap {
 public:
  BinomialHeap();
  BinomialHeap(BNode* node);
  BNode* insert(int key, string payload);
  void meld(BinomialHeap* other);
  BNode* findMin();
  BNode* deleteMin();
  void decreaseKey(BNode* node, int key);
  void makePlot(string filename);
 protected: 
  BNode* root;
  BNode* minNode;
};

#endif /* BINOMIALHEAP_H_ */
