#include "FNode.h"
#include <stdio.h>

class FibonacciHeap {
public:
	FNode *minRoot;
	int size;
	FNode *trees[];

	FibonacciHeap(){};
	FibonacciHeap* insert(int key, char *payload);
	FibonacciHeap* meld(FibonacciHeap *other);
	char* findMin();
	char* deleteMin();	
};
