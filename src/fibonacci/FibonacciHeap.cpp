#include <assert.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "FibonacciHeap.h"
#include "FNode.h"

using namespace std;

FNode* FibonacciHeap::insert(FNode *node, size_t nodeSize) {
  minRoot = !minRoot ? node :
            (minRoot->insert(node),
             node->key < minRoot->key ? node : minRoot);
  size += nodeSize;
}

FNode* FibonacciHeap::insert(int key, string payload) {
  return insert(new FNode(key, payload));
}

void FibonacciHeap::meld(FibonacciHeap *otherHeap) {
  assert(otherHeap);
  if ( FNode *newNode = otherHeap->minRoot )
    insert(newNode, otherHeap->size);
}

FNode* FibonacciHeap::findMin() const {
  return minRoot;
}

FNode* FibonacciHeap::deleteMin() {
  assert(minRoot);

  FNode *c = minRoot->child;
  FNode *d = c;

  // 1. Remove children of minRoot
  if ( c ) {
    do {
      d->parent = NULL;
      d = d->right;
    } while ( c != d );
    minRoot->insert(c);
    minRoot->rank = 0;
    minRoot->child = NULL;
  } else if ( minRoot->right == minRoot ) {
    FNode* result = minRoot;
    minRoot->remove();
    minRoot = NULL;
    return result;
  }

  // 2. Build proper tree
  const size_t i = (sizeof(size)+1) * 8;
  FNode *rank[i];
  memset(rank, 0, sizeof(rank));
  
  c = minRoot->right;
  do {
    int r = c->rank;
    assert(0 <= r && r < i);
    FNode* n2 = c->right;
    while ( rank[r] ) {
      FNode* n = rank[r];
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
  } while ( c != minRoot );

  // 3. Find new min
  FNode* minSeen = NULL;
  c = minRoot->right;
  while ( minRoot != c ) {
    if ( !minSeen || minSeen->key > c->key )
      minSeen = c;
    c->marked = false;
    c = c->right;
  }
  minRoot->remove();
  minRoot = minSeen;

  size--;
  return c;
}

void FibonacciHeap::decreaseKey(FNode *node, int newKey) {
  assert(newKey < node->key);

  node->key = newKey;
  if ( !node->parent ){
    // TODO: Check this for correctness.
    // Node has no parent, only check the invariant.
    if ( newKey < minRoot->key )
      minRoot = node;
    return;
  }

  // Node has parent, we need to update when the invariant is violated.
  if ( newKey < node->parent->key ) {
    FNode *currentParent = node->parent;
    FNode *currentNode = node;

    while ( true ) {
      currentParent->removeChild(currentNode);
      insert(currentNode, 0);

      if ( !currentParent->parent )
        break;

      if ( !currentParent->marked && (currentParent->marked = true) )
        break;

      currentNode = currentParent;
      currentParent = currentParent->parent;
    }
  }
}

void FibonacciHeap::remove(FNode *node) {
  decreaseKey(node, INT_MIN);
  deleteMin();
}

void FibonacciHeap::makeplot(string filename){
  ofstream file;
  string fname = filename+".gv";
  file.open(fname.c_str());
  file << "digraph G {\n";
  if ( minRoot )
    minRoot->makePlot(file);
  file << "}\n" << endl;
  file.close();
  string fname2 = filename;
  string arg = "dot -Tpng " + fname2 + ".gv -o " + fname2 + ".png";
  system(arg.c_str());
}
