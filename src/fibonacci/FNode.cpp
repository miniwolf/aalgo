#include "FNode.h"

FNode::FNode(int key, string payload){
	this->payload = payload;
	this->key = key;
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

	left = NULL;
	right = NULL;
}

void FNode::addChild(FNode *node){
	if(!node){
		return;
	}

	if (node->key < key){
		cerr << "Can not add child with smaller key " << endl;
		exit(1);
	}

	if(child){
		child->insert(node);
	} else {
		child = node;		
		child->parent = this;
	}
	//children should not be marked when added
	node->marked = false;
}

void FNode::removeChild(FNode *node){
	if ( !node) {
		return;
	}
	
	if ( node->parent != this ){
		cerr << "Removing child whos parent we not are" << endl;
		exit(1);
	}
	
	// there are other children left
	if ( rank > 1 && child == node ){
		child = child->right;	
	}
	node->remove();
}



