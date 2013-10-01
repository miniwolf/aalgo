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
#include <vector>

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

  virtual ~FibonacciHeap() {}

  virtual FNode<T>* insert(FNode<T> *node) {
    minRoot = !minRoot ? node :
              (minRoot->insert(node),
               node->key < minRoot->key ? node : minRoot);
    return node;
  }

  virtual FNode<T>* insert(int key, T payload) {
    size++;
    return insert(new FNode<T>(key, payload));
  }

  virtual FNode<T>* findMin() {
    return minRoot;
  }

  /* Cover test it all! */
  virtual FNode<T>* deleteMin() {
    if ( !minRoot ) {
      assert(size > 0);
      return NULL;
    }

    // 1. Remove children of minRoot
    if ( minRoot->child ) {
      FNode<T>* c = minRoot->child;
      do {
        c->parent = NULL;
        c = c->right;
      } while ( c != minRoot->child );
      minRoot->insert(c);
      minRoot->rank = 0;
      minRoot->child = NULL;
    } else if ( minRoot->right == minRoot ) {
      FNode<T>* result = minRoot;
      minRoot->remove();
      minRoot = NULL;
      return result;
    }

    // 2. Build proper tree
    vector<FNode<T>*> rank((sizeof(size) + 1) * 8);
    fill(rank.begin(), rank.end(), (FNode<T>*) NULL);
    FNode<T>* currentP = minRoot->right;
    uint currentRank;
    do {
      currentRank = currentP->rank;
      FNode<T>* current = currentP;
      currentP = currentP->right;
      while ( rank[currentRank] ) {
        FNode<T>* other = rank[currentRank];
        if ( current->key > other->key )
            swap(other, current);
        other->remove();
        current->addChild(other);
        rank[currentRank] = NULL;
        currentRank++;
        if ( currentRank >= rank.size() )
          rank.push_back((FNode<T>*)NULL);
      }
      rank[currentRank] = current;
    } while(currentP != minRoot);

    //3. Find new min
    delete minRoot;
    minRoot = NULL;

    for ( uint d = 0; d < rank.size(); ++d ) {
      if ( rank[d] ) {
        rank[d]->right = rank[d]->left = rank[d];
        insert(rank[d]);
      }
    }

    size--;
    return minRoot;
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
        insert(currentNode);

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
	  decreaseKey(node,(minRoot->key)-1);
    deleteMin();
  }

  virtual int getSize() {
    return size;
  }
};

#endif
