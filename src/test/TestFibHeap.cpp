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

const int TEST_SIZE = 32;

bool testInsert(FibonacciHeap<string> *heap) {
    for ( int i = TEST_SIZE; i > 0; i-- ) {
        heap->insert(TEST_SIZE - i, "test");
        if ( heap->size != TEST_SIZE - i + 1 ) { return false; }
    }
    heap->makePlot("graphs/oBeforeEvil0");
    return true;
}

bool testDeletemin(FibonacciHeap<string> *heap) {
    heap->insert(0,"Evil");
    int lastSeen = 0;
    for ( int j = 0; j < TEST_SIZE; j++ ) {
        string name = "graphs/o" + IntToStr(j);
        heap->makePlot(name);
        FNode<string>* n = heap->deleteMin();
        if ( n->key < lastSeen ) {
            cerr << "ERROR: Did not delete in right order.";
            return false;
        }
        lastSeen = n->key;
        if ( heap->size != TEST_SIZE - j ) { return false; }
    }
    return true;
}

bool TestFibHeap::testFib() {
    FibonacciHeap<string> *heap = new FibonacciHeap<string>();
    bool result = false;
    result = testInsert(heap);
    if ( !result ) { return false; }
    result = testDeletemin(heap);
    if ( !result ) { return false; }
    return result;
}

TestFibHeap::~TestFibHeap() {
}


