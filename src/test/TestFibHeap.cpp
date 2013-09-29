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

bool testCheckTree(const FNode<string>* node) {
    FNode<string>* child;

    child = node->child;
    if ( !child ) { return true; }
    do {
        if ( child->right->left != child ) {
            cerr << "Check node: bad child linked list\n";
            return false;
        }
        
        if ( child->parent != node ) {
            cerr << "Check node: bad child parent\n";
            return false;
        }
        
        if ( !testCheckTree(child) )
            return false;
        
        child = child->right;
    } while (child != node->child);
    return true;
}

bool testCheckTree(const FibonacciHeap<string>* heap) {
    FNode<string>* node;
    for ( node = heap->minRoot->right;
          node != heap->minRoot; node = node->right ) {
        if ( node->right->left != node ) {
            cerr << "Check tree: bad root linked list\n";
            return false;
        }

        if ( node->parent != NULL ) {
            cerr << "Check tree: bad roo parent\n";
            return false;
        }

        if ( !testCheckTree(node) )
            return false;
    }
    return true;       
}

bool testDelete(FibonacciHeap<string> *heap) {
    FNode<string>* node_1 = heap->insert(1, "test");
    FNode<string>* node_2 = heap->insert(2, "test");
    FNode<string>* node_6 = heap->insert(6, "test");
    
    FNode<string>* node_5 = new FNode<string>(5, "test");

    node_2->addChild(node_5);
    FNode<string>* node_3 = new FNode<string>(3, "test");
    FNode<string>* node_4 = new FNode<string>(4, "test");
    FNode<string>* node_7 = new FNode<string>(7, "test");
    node_1->addChild(node_3);
    node_1->addChild(node_4);
    node_1->addChild(node_7);

    FNode<string>* node_8 = new FNode<string>(8, "test");
    FNode<string>* node_9 = new FNode<string>(9, "test");
    node_7->addChild(node_8);
    node_8->addChild(node_9);
    heap->remove(node_9);
    //if ( node_9 != heap->remove(node_9) ) { return false; }
    if ( node_1->key != heap->findMin()->key ) { return false; }

    /*if ( !node_8->marked ) { return false; }

    if ( node_1->parent ) { return false; }
    if ( node_2->parent ) { return false; }
    if ( node_6->parent ) { return false; }

    if ( node_1 != node_3->parent ) { return false; }
    if ( node_1 != node_4->parent ) { return false; }
    if ( node_1 != node_7->parent ) { return false; }
    if ( node_1 != node_8->parent ) { return false; }

    if ( node_1 != node_3->parent ) { return false; }

    if ( node_1 != node_3->parent ) { return false; }
    if ( node_1 != node_3->parent ) { return false; }
    if ( node_1 != node_3->parent ) { return false; }
    if ( node_1 != node_3->parent ) { return false; }

    if ( node_1 != node_3->parent ) { return false; }*/
}

bool testInsert(FibonacciHeap<string> *heap) {
    FNode<string>* node;
    for ( int i = TEST_SIZE; i > 0; i-- ) {
        node = heap->insert(TEST_SIZE - i, "test");
        if ( !testCheckTree(node) ) { return false; }
        if ( heap->size != TEST_SIZE - i + 1 ) { return false; }
    }
    return true;
}

bool testDeletemin(FibonacciHeap<string> *heap) {
    heap->makePlot("graphs/oBeforeEvil0");
    heap->insert(0,"Evil");
    int lastSeen = 0;
    FNode<string>* minNode = heap->findMin();
    for ( int j = 0; j < TEST_SIZE; j++ ) {
        string name = "graphs/o" + IntToStr(j);
        heap->makePlot(name);
        FNode<string>* n = heap->deleteMin();
        if ( n != minNode ) { return false; }
        if ( n->key < lastSeen ) {
            cerr << "ERROR: Did not delete in right order.";
            return false;
        }
        lastSeen = n->key;
        if ( heap->size != TEST_SIZE - j ) { return false; }
        minNode = heap->findMin();
        if ( !testCheckTree(minNode) ) { return false; }
    }
    return true;
}

bool neDecreaseKeyRestructuring(FibonacciHeap<string> *heap) {
    FNode<string>* node_1 = heap->insert(1, "test");
    FNode<string>* node_2 = heap->insert(2, "test");
    FNode<string>* node_6 = heap->insert(6, "test");
    
    FNode<string>* node_5 = new FNode<string>(5, "test");

    node_2->addChild(node_5);
    FNode<string>* node_3 = new FNode<string>(3, "test");
    FNode<string>* node_4 = new FNode<string>(4, "test");
    FNode<string>* node_7 = new FNode<string>(7, "test");
    node_1->addChild(node_3);
    node_1->addChild(node_4);
    node_1->addChild(node_7);

    FNode<string>* node_8 = new FNode<string>(8, "test");
    FNode<string>* node_9 = new FNode<string>(9, "test");
    node_7->addChild(node_8);
    node_8->addChild(node_9);

    node_4->marked = true;
    node_7->marked = true;
    node_8->marked = true;

    heap->decreaseKey(node_9, 0);

    if ( 0 != node_9->key ) { return false; }

    if ( !node_4->marked ) { return false; }

    if ( node_1->parent ) { return false; }
    if ( node_2->parent ) { return false; }
    if ( node_6->parent ) { return false; }
    if ( node_9->parent ) { return false; }
    if ( node_8->parent ) { return false; }
    if ( node_7->parent ) { return false; }

    if ( node_1 != node_3->parent ) { return false; }
    if ( node_1 != node_4->parent ) { return false; }

    if ( node_2 != node_5->parent ) { return false; }

    if ( node_2 != node_5->parent ) { return false; }
    return true;
}

/**
 * The value does change if you don't change the value
 */
bool neDecreaseKeyValue(FibonacciHeap<string> *heap) {
    FNode<string>* node_1 = heap->insert(1, "test");
    heap->decreaseKey(node_1, node_1->key);
    if ( 1 != node_1->key ) { return false; }
    return true;
}

/**
 * Test reconstruction correctly.
 */
bool neDeleteMinReconstruction(FibonacciHeap<string>* heap) {
    FNode<string>* node_1 = heap->insert(1, "test");
    FNode<string>* node_2 = heap->insert(2, "test");
    FNode<string>* node_6 = heap->insert(6, "test");
    
    FNode<string>* node_5 = new FNode<string>(5, "test");

    node_2->addChild(node_5);
    FNode<string>* node_3 = new FNode<string>(3, "test");
    FNode<string>* node_4 = new FNode<string>(4, "test");
    FNode<string>* node_7 = new FNode<string>(7, "test");
    node_1->addChild(node_3);
    node_1->addChild(node_4);
    node_1->addChild(node_7);

    FNode<string>* node_8 = new FNode<string>(8, "test");
    FNode<string>* node_9 = new FNode<string>(9, "test");
    node_7->addChild(node_8);
    node_8->addChild(node_9);

    if ( 1 != heap->deleteMin()->key ) { return false; }
    if ( 2 != heap->findMin()->key ) { return false; }
    
    if ( node_2->parent != NULL ) { return false; }
    if ( node_3->parent != NULL ) { return false; }
    if ( node_6->parent != NULL ) { return false; }

    if ( node_2 != node_5->parent ) { return false; }

    if ( node_3 != node_4->parent ) { return false; }
    if ( node_3 != node_7->parent ) { return false; }

    if ( node_7 != node_8->parent ) { return false; }
    if ( node_8 != node_9->parent ) { return false; }
    return true;
}

/**
 * Test emptiness.
 * Test with one item in the heap.
 * Test emptiness after deletion.
 */
bool neDeleteMin(FibonacciHeap<string>* heap) {
    if ( heap->deleteMin() ) { return false; }
    heap->insert(1, "test");
    if ( heap->deleteMin()->key != 1 ) { return false; }
    heap->insert(1, "test");
    if ( heap->deleteMin()->key != 1 ) { return false; }
    if ( heap->deleteMin() ) { return false; }
    return true;
}

bool neMinNode(FibonacciHeap<string>* heap) {
    if ( heap->findMin() != NULL ) { return false; }
    
    heap->insert(1, "test");
    if ( heap->findMin()->key != 1 ) { return false; }

    heap->insert(2, "test");
    if ( heap->findMin()->key != 1 ) { return false; }

    heap->insert(0, "test");
    if ( heap->findMin()->key != 0 ) { return false; }
    return true;
}

bool sampleTest(FibonacciHeap<string>* heap) {
    // Sample test
    FNode<string>* node_1 = heap->insert(1, "test");
    FNode<string>* node_2 = heap->insert(2, "test");
    FNode<string>* node_6 = heap->insert(6, "test");
    FNode<string>* node_5 = new FNode<string>(5, "test");

    node_2->addChild(node_5);

    node_1->addChild(new FNode<string>(3, "test"));
    node_1->addChild(new FNode<string>(4, "test"));
    FNode<string>* node_7 = new FNode<string>(7, "test");
    node_1->addChild(node_7);

    FNode<string>* node_8 = new FNode<string>(8, "test");
    node_7->addChild(node_8);
    node_8->addChild(new FNode<string>(9, "test"));

    if ( 3 != heap->size ) { return false; }
    if ( 1 != heap->findMin()->key ) { return false; }
    return true;
}

FibonacciHeap<string>* setup() {
    return new FibonacciHeap<string>();
}

bool TestFibHeap::testFib() {
    FibonacciHeap<string> *heap = new FibonacciHeap<string>();
    bool result = false;
    result = testInsert(heap);
    if ( !result ) { return false; }
    result = testDeletemin(heap);
    if ( !result ) { return false; }
    result = testCheckTree(heap);
    if ( !result ) { return false; }
    result = sampleTest(setup());
    if ( !result ) { return false; }
    result = neMinNode(setup());
    if ( !result ) { return false; }
    result = neDeleteMin(setup());
    if ( !result ) { return false; }
    result = neDeleteMinReconstruction(setup());
    if ( !result ) { return false; }
    result = neDecreaseKeyValue(setup());
    if ( !result ) { return false; }
    result = neDecreaseKeyRestructuring(setup());
    if ( !result ) { return false; }
    //result = testDelete(setup());
    return result;
}

TestFibHeap::~TestFibHeap() {
}
