#include "FNode.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class FibonacciHeap {
public:
	FNode *minRoot;
	int size;
	FNode *trees[];

	FibonacciHeap(){};
	FibonacciHeap* insert(int key, string payload);
	FibonacciHeap* meld(FibonacciHeap *other);
	string findMin();
	string deleteMin();	
};
