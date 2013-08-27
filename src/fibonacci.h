class FNode {
public:
	FNode *left;
	FNode *right;
	FNode *parent;
	FNode *child;
	
	int rank;
	int key;

 	bool marked;

	char *payload;

	FNode(int key, char *payload);

};

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
