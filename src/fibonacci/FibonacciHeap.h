#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <assert.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Heap.h"
#include "FNode.h"

using namespace std;

#define cover() assert(false);

template <class T>
class FibonacciHeap : public Heap<T> {
public:
  FNode<T> *minRoot;
  int size;

  FibonacciHeap() {
    minRoot = NULL;
    size = 0;
  }

  virtual ~FibonacciHeap() {

  }

  virtual FNode<T>* insert(FNode<T> *node) {
    if(!minRoot){
      minRoot = node;
    } else {
      minRoot->insert(node);
      if(node->key < minRoot->key ){
	minRoot = node;
      }
    }
    size++;
    return node;
  }

  virtual FNode<T>* insert(int key, T payload) {
    FNode<T>* f = new FNode<T>(key, payload);
    return insert(f);
  }

  virtual FNode<T>* findMin() {
    return minRoot;
  }

  /* Cover test it all! */
  virtual FNode<T>* deleteMin() {
    if(!minRoot){
      assert(size>0);
      return NULL;
    }
    FNode<T>* c = minRoot->child;
    FNode<T>* d = c;
    // 1. Remove children of minRoot
    if ( c ) {
      do {
        d->parent = NULL;
        assert(d->right);
        d = d->right;
      } while(c != d);

      minRoot->insert(c);
      minRoot->rank = 0;
      if ( minRoot->child) { minRoot->child->parent = NULL; }
      minRoot->child = NULL;
    } else if ( minRoot->right == minRoot ) {
      FNode<T>* result = minRoot;
      minRoot->remove();
      minRoot = NULL;
      return result;
    }
    // 2. Build proper tree
    int i = ceil(log2(size)*4);

    FNode<T>** rank = new FNode<T>*[i];
    for(int slap = 0; slap < i ; slap++){
      rank[slap] = NULL;
    }

    //cout << "1: "<< rank << endl;

    c = minRoot->right;
    do {
      int r = c->rank;
      assert(0 <= r && r < i);
      FNode<T>* n2 = c->right;
      while( rank[r] ) {
        FNode<T>* n = rank[r];
        if ( n->key < c->key ) {
          assert(c != n);
          c->remove();
          n->addChild(c);
          c = n;
        } else {
          assert(c != n);
          n->remove();
          c->addChild(n);
        }
        rank[r] = NULL;
        r++;
      }
      rank[r] = c;
      c = n2;
    } while(c != minRoot);
    //3. Find new min
    FNode<T>* minSeen = NULL;

    c = minRoot->right;
    while ( minRoot != c ) {
      if ( !minSeen || minSeen->key > c->key )
        minSeen = c;
      c->marked = false;
      c->parent = NULL;
      c = c->right;
    }

    minRoot->remove();

    // before deleting the old minRoot, go through the whole tree, check if someone knows minroot
    // this is SLOW
   // assert(!(minSeen->knows(minRoot)));

    minRoot = minSeen;

    size --;
    //cout << "2: "<<rank << endl;
    delete []rank;
    return c;
  }

  void decreaseKey(Node<T> *node, int newKey){
    decreaseKey(dynamic_cast<FNode<T>*>(node), newKey);
  }

  void decreaseKey(FNode<T> *node, int newKey) {
    assert(newKey < node->key);
    node->key = newKey;
    if ( !(node->parent) ) {
      // TODO: Check this for correctness.
      // node has no parent, only check the invariant.
      if ( newKey < minRoot->key )
        minRoot = node;
      return;
    }

    // node has parent, we need to update when the invariant is violated.
    if ( newKey < node->parent->key ) {
      FNode<T> *currentParent = node->parent;
      FNode<T> *currentNode = node;

      while ( true ) {
        currentParent->removeChild(currentNode);
        insertNode(currentNode);

        if ( !(currentParent->parent) )
            break;

        if ( !(currentParent->marked) ){
          currentParent->marked = true;
          break;
        }

        currentNode = currentParent;
        currentParent = currentParent->parent;
      }
    }
  }

  virtual void makePlot(string filename) {
    ofstream file;
    string fname = filename + ".gv";
    file.open(fname.c_str());
    file << "digraph G {\n";
    if ( minRoot )
      minRoot->makePlot(file);
    file << "}\n" << endl;
    file.close();
    string fname2 = filename;
    string arg = "dot -Tps " + fname2 + ".gv -o "+fname2+".ps";
    system(arg.c_str());
  }

  void meld(FibonacciHeap<T> *otherHeap) {
    assert(otherHeap);
    if ( FNode<T> *newNode = otherHeap->minRoot )
      insert(newNode, otherHeap->size);
  }

  virtual void remove(Node<T>* node){
    remove(dynamic_cast<FNode<T>*> (node));
  }

  virtual void remove(FNode<T> *node) {
	decreaseKey(node,INT_MIN);
    FNode<T>* test = deleteMin();
    assert(test == node);
  }

  virtual int getSize() {
    return size;
  }

  void insertNode(FNode<T> *node) {
    if ( !minRoot )
      minRoot = node;
    else {
      minRoot->insert(node);
      if ( node->key < minRoot->key )
        minRoot = node;
    }
  }
};

#endif
