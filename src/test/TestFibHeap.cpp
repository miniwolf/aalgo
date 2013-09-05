#include "TestFibHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>

TestFibHeap::TestFibHeap() {
	srand(45);
}


template <typename ROFL>
string IntToStr(ROFL tmp){
    std::ostringstream out;
    out << tmp;
    return out.str();
}

bool TestFibHeap::testFib() {

	FibonacciHeap *heap = new FibonacciHeap();
	int testSize = 32;

	for( int i = testSize ; i > 0; i--) {
		int key = testSize-i;

		heap->insert(key, "test");
	}
	string name0 = "graphs/oBeforeEvil0";
	heap->makeplot(name0);

	heap->insert(0,"Evil");
	int lastSeen = 0;
	for( int j = 0 ; j < testSize; j++) {
		string name = "graphs/o" + IntToStr(j);
		heap->makeplot(name);
		FNode* n = heap->deleteMin();
		if(n->key<lastSeen){
		  cerr << "ERROR: Did not delete in right order.";
		}
		cout << "Deleted min element: " << n->key << endl;
	}

	return false;
}

TestFibHeap::~TestFibHeap() {
}


