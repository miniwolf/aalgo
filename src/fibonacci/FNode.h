#ifndef FNODE_H_
#define FNODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Node.h"
using namespace std;

template <class T>
class FNode : public Node<T>{
 public:
	FNode<T> *left;
	FNode<T> *right;
	FNode<T> *parent;
	FNode<T> *child;

 	bool marked;

	int rank;

	FNode(int key, T payload);

	void insert(FNode<T> *node);
	void remove();
	void addChild(FNode<T> *node);
	void removeChild(FNode<T> *node);
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
