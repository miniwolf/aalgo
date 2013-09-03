#include "FNode.h"
#include <math.h>
#include <limits.h>
#include <iostream>
#include <fstream>
using namespace std;

FNode::FNode(int key, string payload){
	this->payload = payload;
	this->key = key;
	child = NULL;
	parent = NULL;
	left = this;
	right = this;
	rank = 0;
	marked = false;
}

void FNode::insert(FNode *node){
	if( !node ){
		return;
	}
	if(parent){
		parent->rank++;
	}
	FNode *x = right;
	FNode *y = node->left;
	right = node;
	node->left = this;
	node->parent = parent;
	x->left = y;
	y->right = x;
}

void FNode::remove(){

	if (parent){
		if ( parent->rank == 1 ){
			parent->child = NULL;
		}
		parent->rank--;

		parent = NULL;
	}

	left->right = right;
	right->left = left;

	left = this;
	right = this;
}

void FNode::addChild(FNode *node){
	if(!node){
		return;
	}

	if (node->key < key){
		cout << "Can not add child with smaller key " << endl;
		exit(1);
	}

	if(child){
		child->insert(node);
	} else {
		child = node;		
		child->parent = this;
		rank = 1;
	}
	//children should not be marked when added
	node->marked = false;
}

void FNode::removeChild(FNode *node){
	if ( !node) {
		return;
	}
	
	if ( node->parent != this ){
		cout << "Removing child whos parent we not are" << endl;
		exit(1);
	}
	
	// there are other children left
	if ( rank > 1 && child == node ){
		child = child->right;	
	}
	node->remove();
}

void FNode::subplot(ofstream &file){
	if ( child ){
		file <<  payload << key  << " -> "  << child->payload << child->key << " [style=dashed,color=red] \n";
	}

	if ( parent ){
		file  << payload << key << " -> "  << parent->payload << parent->key << " [style=dotted,color=blue] \n";
	}

	file  << payload << key << " -> "  << right->payload << right->key << "\n";
	file  << payload << key << " -> "  << left->payload << left->key << " [color=green] \n";

	file << "{rank=same; "  << payload << key << " " << right->payload << right->key << "}\n";

	file << "{ \n";
	if ( child ){
		child->makePlot(file);
	}
	file << "} \n";
}

void FNode::makePlot(ofstream &file){
	subplot(file);

	FNode *temp = right;

	while(!(temp == this)){
		temp->subplot(file);
		temp = temp->right;
	}

}



