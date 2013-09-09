#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "main.h"

using namespace std;

string IntToString(int num) {
      ostringstream myStream;
	  myStream << num << flush;
	  return myStream.str();
}

int main(int argc, char *argv[]) {
  /*	FibonacciHeap *heap = new FibonacciHeap;
	 heap->insert(13,"Dimmer");
	 heap->insert(16,"Hunter");
	cout << "Element One: " << heap->minRoot->payload << endl;
	cout << "Element Two: " << heap->minRoot->right->payload << endl;

	FibonacciHeap *heap2 = new FibonacciHeap;
	 heap2->insert(13,"Dimmer");
	 heap2->insert(16,"Hunter");
  */
	 TestFibHeap *test = new TestFibHeap();
	 test->testFib();

}


