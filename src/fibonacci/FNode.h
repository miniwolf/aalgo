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
