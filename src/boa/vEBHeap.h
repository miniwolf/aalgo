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
  vEBHeap(int universe):mUniverse(universe) {
    tree = new vEB(universe);
    mNodeArray = new Node<T>*[universe];
    for(int i = 0; i<universe; i ++){
      mNodeArray[i] = NULL;
    }
  }
  
  virtual ~vEBHeap() {
    for(int i = 0; i < mUniverse; i ++){
      delete mNodeArray[i];
    }
    delete[] mNodeArray;
    delete tree;
  }
  
  virtual int getComparisons(){
    return 0;
  }
  
  virtual Node<T>* insert(Node<T>* node) {
    tree->insert(node->key);
    return setNode(node->key, node->payload);
    
  }
  
  virtual Node<T>* insert(int key, T payload) {
    tree->insert(key);
    return setNode(key, payload);
  }
  
  virtual Node<T>* findMin() {
    return tree->min == tree->NIL?NULL:getNode(tree->min);
  }
  
  virtual Node<T>* deleteMin() {
    int res = tree->deleteMin();
    if(res == tree->NIL){
      return NULL;
    }
    Node<T>* node = removeNode(res);
    return node;
  }
  
  void decreaseKey(Node<T> *node, int newKey){
    tree->decreaseKey(node->key, newKey);
    removeNode(node->key);
    node->key = newKey;
    setNode(node);
  }
  
  virtual void makePlot(string) {  }
  
  virtual void remove(Node<T>* node){
    removeNode(node->key);
  }
  
  virtual int getSize() {
    return tree->count;
  }
  
private:
  int mUniverse;
  Node<T>** mNodeArray;

  Node<T>* getNode(int key){
      return mNodeArray[key];
  }

  Node<T>* setNode(int key, T payload){
    return mNodeArray[key]? mNodeArray[key]:mNodeArray[key] = new vEBNode<T>(key, payload);
  }

  Node<T>* setNode(Node<T>* node){
    return mNodeArray[node->key]? mNodeArray[node->key]:mNodeArray[node->key] = node;
  }

  Node<T>* removeNode(int key){
    Node<T>* n = getNode(key);
    mNodeArray[key]  = NULL;
    return n;
  }

};

#endif
