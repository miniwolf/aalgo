#include "fibonacci.h"
#include <stdio.h>

FNode::FNode(int key, char *payload){
	this->payload = payload;
	this->key = key;

}

FibonacciHeap* FibonacciHeap::insert(int key, char *payload){
	FNode *node = new FNode(key, payload);
	node->left = node;
	node->right = node;
	FibonacciHeap *heap = new FibonacciHeap;
	heap->minRoot = node;
	return meld(heap);
}

FibonacciHeap* FibonacciHeap::meld(FibonacciHeap *otherHeap){
	FibonacciHeap *result = new FibonacciHeap;
	FNode *minRoot2 = otherHeap->minRoot;
	
	if ( minRoot2 == NULL ){
		delete otherHeap;
		return this;
	} else if ( minRoot == NULL) {
		delete this;
		return otherHeap;
	}

	FNode *a = minRoot;
	FNode *b = minRoot2;

	FNode *x = a->right;
	FNode *y = b->left;

	a->right = b;
	b->left = a;

	x->left = y;
	y->right = x;

	if ( a->key <= b->key ) {
		result->minRoot = a	;
	} else {
		result->minRoot = b	;
	}

	return result;
}


	
