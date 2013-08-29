#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class FNode {
public:
	FNode *left;
	FNode *right;
	FNode *parent;
	FNode *child;

	int rank;
	int key;

 	bool marked;

	string payload;

	FNode(int key, string payload);

	void insert(FNode *node);
	void remove();
	void addChild(FNode *node);
	void removeChild(FNode *node);
};
