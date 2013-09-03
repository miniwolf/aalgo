#include "FibonacciHeap.h"
#include <math.h>
#include <limits.h>
#include <iostream>
#include <fstream>
using namespace std;

FNode* FibonacciHeap::insert(int key, string payload){
  FNode *node = new FNode(key, payload);

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

void FibonacciHeap::meld(FibonacciHeap *otherHeap){
  if ( !otherHeap) {
    return;
  }
  FNode *minRoot2 = otherHeap->minRoot;

  if ( !minRoot2 ){
    return;
  }

  if ( minRoot ) {
    minRoot->insert( minRoot2 );
    size += otherHeap->size;

    if ( minRoot->key > minRoot2->key ) {
      minRoot = minRoot2;
    }
  } else {
    minRoot = minRoot2;
    size = otherHeap->size;
  }
}

FNode* FibonacciHeap::findMin(){
  return minRoot;
}

FNode* FibonacciHeap::deleteMin(){

  FNode* c = minRoot->child, *d = c;

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
    FNode* m = minRoot;
    minRoot->remove();
    minRoot = NULL;
    return m;
  }
  // 2. Build proper tree
  int i;
  i = int(ceil(log2(size) + 2));
  FNode *rank[i];
  for(int j =0; j<i; j++){
    rank[j] = NULL;
  }


  c = minRoot->right;
  do{
    int r = c->rank;
    while(rank[r]){
      FNode* n = rank[r];
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
    c = c->right;
  } while(c != minRoot);


  //3. Find new min
  FNode* minSeen = NULL;
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

void FibonacciHeap::insertNode(FNode *node){
	if ( !minRoot ) {
		minRoot = node;
	} else {
		minRoot->insert(node);
		if( node->key < minRoot->key ){
			minRoot = node;
		}
	}
}

void FibonacciHeap::decreaseKey(FNode *node, int newKey){
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
		FNode *currentParent = node->parent;
		FNode *currentNode = node;

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

void FibonacciHeap::remove(FNode *node){
	decreaseKey(node,INT_MIN);
	deleteMin();
}


void FibonacciHeap::makeplot(string filename){
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
