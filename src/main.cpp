#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>


string IntToString(int num)
{     ostringstream myStream; //creates an ostringstream object
	  myStream<<num<<flush;
	  /*outputs the number into the string stream and then flushes
	  the buffer (makes sure the output is put into the stream)*/
	  return myStream.str(); //returns the string form of the stringstream object
}
using namespace std;

int main(int argc, char *argv[]){
	FibonacciHeap *heap = new FibonacciHeap;
	 heap->insert(13,"Dimmer");
	 heap->insert(16,"Hunter");
	cout << "Element One: " << heap->minRoot->payload << endl;
	cout << "Element Two: " << heap->minRoot->right->payload << endl;

	FibonacciHeap *heap2 = new FibonacciHeap;
	 heap2->insert(13,"Dimmer");
	 heap2->insert(16,"Hunter");

	 TestFibHeap *test = new TestFibHeap();
	 test->testFib();

}


