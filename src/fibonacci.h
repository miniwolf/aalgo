class FNode {
	FNode *left;
	FNode *right;
	FNode *parent;
	FNode *child;
	
	int rank;

 	bool marked;

	char *payload;
};

class FibonacciHeap {
	FNode *minroot;
 public:
	FibonacciHeap(int a);
	void insert(int key, char *payload);
	FibonacciHeap meld(FibonacciHeap *other);
	char* findMin();
	char* deleteMin();	
};
