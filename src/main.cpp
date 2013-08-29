#include "main.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]){
	FibonacciHeap *heap = new FibonacciHeap;
	heap = heap->insert(13,"Dimmer");
	heap = heap->insert(16,"Hunter");
	cout << "Element One: " << heap->minRoot->payload << endl;
	cout << "Element Two: " << heap->minRoot->right->payload << endl;
}
