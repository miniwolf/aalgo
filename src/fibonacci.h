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
	FNode *root;
 public:
	FibonacciHeap(int a);
};
