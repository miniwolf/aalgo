#ifndef FNODE_H_
#define FNODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Node.h"
using namespace std;

class FNode : public Node{
 public:
	FNode *left;
	FNode *right;
	FNode *parent;
	FNode *child;

 	bool marked;

	int rank;

	FNode(int key, string payload);

	void insert(FNode *node);
	void remove();
	void addChild(FNode *node);
	void removeChild(FNode *node);
	void subplot(ofstream &file);

	virtual void makePlot(ofstream &file){
	  
	  subplot(file);

	  FNode *temp = right;

	  while(!(temp == this)){
	    temp->subplot(file);
	    temp = temp->right;
	  }
	  
	}
};

#endif
