#ifndef VEB_HEAP_H
#define VEB_HEAP_H

#include <assert.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Heap.h"
#include "vEBNode.h"
#include "vEB.h"


using namespace std;

#define cover() assert(false);

template <class T>
class vEBHeap : public Heap<T> {
public:
  vEB* tree;
  vEBHeap(int universe) {
      tree = new vEB(universe);
  }

  virtual ~vEBHeap() {  }

  virtual int getComparisons(){
    return 0;
  }

  virtual vEBNode<T>* insert(vEBNode<T>* node) {
      tree->insert(node->key);
    return setNode(node->key, node->payload);

  }

  virtual vEBNode<T>* insert(int key, T payload) {
        tree->insert(key);
      return setNode(key, payload);
  }

  virtual vEBNode<T>* findMin() {
    return getNode(tree->min);
  }

  virtual vEBNode<T>* deleteMin() {
      vEBNode<T>* node = removeNode(tree->deleteMin());
      return node;
  }

  void decreaseKey(Node<T> *node, int newKey){
    tree->decreaseKey(node->key, newKey);
    removeNode(node->key);
    node->key = newKey;
    setNode(newKey, node->payload);
  }

  virtual void makePlot(string) {  }

  virtual void remove(Node<T>* node){
    removeNode(node->key);
  }

  virtual int getSize() {
      return tree->count;
  }

private:
  vEBNode<T>* getNode(int key){
      return new vEBNode<T>(key);
  }

  vEBNode<T>* setNode(int key, T ){
      return getNode(key);

  }

  vEBNode<T>* removeNode(int key){
      return getNode(key);
  }

};

#endif
