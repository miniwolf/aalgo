#ifndef FIBONACCI_HEAP_H_
#define FIBONACCI_HEAP_H_

#include "../Heap.h"
#include "FNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class FibonacciHeap : public Heap<T> {
 public:
  FNode<T> *minRoot;
  int size;

  FibonacciHeap(){
    minRoot=NULL;
    size=0;
  }

  virtual FNode<T>* insert(int key, T payload){
    
    FNode<T> *node = new FNode<T>(key, payload);
    
    if ( minRoot ){
      minRoot->insert(node);
      if ( minRoot->key > key ){
	minRoot = node;
      }
    } else {
      minRoot = node;
    }

    size++;

    return node;
  }

  virtual FNode<T>* findMin(){
    return minRoot;
  }

  virtual FNode<T>* deleteMin(){

    FNode<T>* c = minRoot->child, *d = c;

    // 1. Remove children of minRoot
    if(c){
      do {
	d->parent = NULL;
	d = d->right;
      } while(c != d);
      minRoot->insert(c);
      minRoot->rank = 0;
      minRoot->child = NULL;
    } else if(minRoot->right == minRoot) {
      FNode<T>* m = minRoot;
      minRoot->remove();
      minRoot = NULL;
      return m;
    }

    // 2. Build proper tree
    int i;
    i = int(ceil(log2(size) + 2));
    FNode<T> *rank[i];
    for(int j =0; j<i; j++){
      rank[j] = NULL;
    }

  
    c = minRoot->right;
    do{
      int r = c->rank;
      FNode<T>* n2 = c->right;
      while(rank[r]){
	FNode<T>* n = rank[r];
	if(n->key < c->key){
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
    while(minRoot != c){
      //minSeen= !minSeen || minSeen->key > c->key?c:minSeen;
      if(!minSeen){
	minSeen = c;
      } else {
	if ( minSeen->key > c->key){
	  minSeen = c;
	}
      }

      c->marked = false;
      c = c->right;
    }
    c = minRoot;
    minRoot->remove();

    minRoot = minSeen;

    size --;
    return c;
  }


  
  virtual void decreaseKey(Node<T> *node, int newKey){}
  virtual void decreaseKey(FNode<T> *node, int newKey){

    if( newKey >= node->key ) {
      return; // can only decrease keys, not increase.	
    }

    node->key = newKey;
    if ( !node->parent ){
      // node has no parent, only check the invariant
      if ( newKey < minRoot->key ){
	minRoot = node;
      }
      return;
    }

    // node has parent, we need to update when the invariant is violated.
    if ( newKey < node->parent->key ) {
      FNode<T> *currentParent = node->parent;
      FNode<T> *currentNode = node;

      while(true){
	currentParent->removeChild(currentNode);
	insertNode(currentNode);

	if (!currentParent->parent){
	  break;
	} else if ( !currentParent->marked) {
	  currentParent->marked = true;
	  break;
	} else {
	  currentNode = currentParent;
	  currentParent = currentParent->parent;
	}
      }
    }
  }


  virtual void makePlot(string filename){
    ofstream file;
    string fname = filename+".gv";
    file.open(fname.c_str());
    file << "digraph G {\n";
    if( minRoot ){
      minRoot->makePlot(file);
    }
    file << "}\n" << endl;
    file.close();
    string fname2 = filename;
    string arg = "dot -Tps " + fname2 + ".gv -o "+fname2+".ps";
    system(arg.c_str());
  }


  void meld(FibonacciHeap<T> *other);
  void remove(FNode<T> *node);
  void insertNode(FNode<T> *node);
};

#endif
