#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <stddef.h>
#include <string>

class FNode;

class FibonacciHeap {
public:
  FNode *minRoot;
  size_t size;

  FibonacciHeap() : minRoot(NULL), size(0) { }
  FNode* insert(FNode* node, size_t nodeSize = 1);
  FNode* insert(int key, std::string payload);
  void meld(FibonacciHeap *other);
  FNode* findMin() const;
  FNode* deleteMin();
  void decreaseKey(FNode *node, int key);
  void remove(FNode *node);
  void makeplot(std::string filename);
};

#endif
