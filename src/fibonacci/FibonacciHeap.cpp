#include "FibonacciHeap.h"
#include <math.h>
#include <limits.h>
#include <iostream>
#include <fstream>
using namespace std;

template <class T>
void FibonacciHeap<T>::meld(FibonacciHeap<T> *otherHeap){
  if ( !otherHeap) {
    return;
  }
  FNode<T> *minRoot2 = otherHeap->minRoot;

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


template <class T>
void FibonacciHeap<T>::insertNode(FNode<T> *node){
  if ( !minRoot ) {
    minRoot = node;
  } else {
    minRoot->insert(node);
    if( node->key < minRoot->key ){
      minRoot = node;
    }
  }
}


template <class T>
void FibonacciHeap<T>::remove(FNode<T> *node){
  decreaseKey(node,INT_MIN);
  deleteMin();
}

