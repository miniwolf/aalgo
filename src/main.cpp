#include "main.h"
#include <stdio.h>
#include <stdlib.h>
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
	 cout << "Deleted min element: " << heap2->deleteMin()->payload << endl;

}
