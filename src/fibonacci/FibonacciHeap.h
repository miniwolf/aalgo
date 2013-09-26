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

  virtual FNode<T>* insert(FNode<T> *node, size_t nodeSize = 1) {
    minRoot = !minRoot ? node :
              (minRoot->insert(node),
               node->key < minRoot->key ? node : minRoot);
    size += nodeSize;
    return node;
  }

  virtual FNode<T>* insert(int key, T payload) {
    return insert(new FNode<T>(key, payload));
  }

  virtual FNode<T>* findMin() {
    return minRoot;
  }

  /* Cover test it all! */
  virtual FNode<T>* deleteMin() {
    if ( !minRoot ) { return NULL; }
    FNode<T>* c = minRoot->child, *d = c;

    // 1. Remove children of minRoot
    if ( c ) {
      do {
        d->parent = NULL;
        d = d->right;
      } while(c != d);
      minRoot->insert(c);
      minRoot->rank = 0;
      minRoot->child = NULL;
    } else if ( minRoot->right == minRoot ) { // will this ever be true
      FNode<T>* result = minRoot;
      minRoot->remove();
      minRoot = NULL;
      return result;
    }

    // 2. Build proper tree
    const size_t i = (sizeof(size) + 1) * 8;
    FNode<T> *rank[i];
    memset(rank, 0, sizeof(rank));

    c = minRoot->right;
    do {
      int r = c->rank;
      assert(0 <= r && r < i);
      FNode<T>* n2 = c->right;
      while( rank[r] ) {
        FNode<T>* n = rank[r];
        if ( n->key < c->key ) {
          c->remove();
          n->addChild(c);
          c = n;
        } else {
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
      c = c->right;
    }
    minRoot->remove();
    minRoot = minSeen;

    size --;
    return c;
  }
  
  virtual void decreaseKey(Node<T> *node, int newKey){}
  virtual void decreaseKey(FNode<T> *node, int newKey) {
    assert(newKey <= node->key);
    node->key = newKey;
    if ( !node->parent ) {
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

        if ( !currentParent->parent )
            break;

        if ( !currentParent->marked && (currentParent->marked = true) )
            break;
        
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

  void remove(FNode<T> *node) {
	decreaseKey(node,INT_MIN);
    deleteMin();
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
