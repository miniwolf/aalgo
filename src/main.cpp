#include "main.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	FibonacciHeap *heap = new FibonacciHeap;
	heap = heap->insert(13,"Dimmer");
	heap = heap->insert(16,"Hunter");
	printf("Element One: %s",heap->minRoot->payload);
	printf("Element Two: %s",heap->minRoot->right->payload);
}
