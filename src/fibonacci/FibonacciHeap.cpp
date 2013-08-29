#include "FibonacciHeap.h"
#include <math.h>

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
  FNode* rank[i = int(ceil(log2(size)+1))];
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

  FNode* minSeen;
  c = minRoot->right;
  while(minRoot != c){
    minSeen= !minSeen || minSeen->key > c->key?c:minSeen;
    c = c->right;
  }
  c = minRoot;
  minRoot->remove();
  minRoot = minSeen;

  size --;
  return c;

}
