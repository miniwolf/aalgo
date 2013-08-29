#include "FibonacciHeap.h"

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

string FibonacciHeap::findMin(){
	return minRoot->payload;
}

