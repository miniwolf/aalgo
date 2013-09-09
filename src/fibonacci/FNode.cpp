#include <assert.h>
#include <math.h>
#include <limits.h>
#include <iostream>
#include <fstream>

#include "FNode.h"

using namespace std;

FNode::FNode(int key, string payload) : payload(payload), key(key) {
	child = NULL;
	parent = NULL;
	left = this;
	right = this;
	rank = 0;
	marked = false;
}

void FNode::insert(FNode *node) {
    assert(node);

	if ( parent )
		parent->rank++;

	FNode *x = right;
	FNode *y = node->left;
	right = node;
	node->left = this;
	node->parent = parent;
	x->left = y;
	y->right = x;
}

void FNode::remove() {
	if (parent) {
		if ( parent->rank == 1 )
			parent->child = NULL;
		parent->rank--;
		parent = NULL;
	}

	left->right = right;
	right->left = left;

	left = this;
	right = this;
}

void FNode::addChild(FNode *node) {
    assert(node);
    assert(key <= node->key);

	if ( child )
		child->insert(node);
	else {
		child = node;		
		child->parent = this;
		rank = 1;
	}
	// Children should not be marked when added.
	node->marked = false;
}

void FNode::removeChild(FNode *node) {
    assert(node);
	assert(node->parent == this);
	
	// There are other children left
	if ( rank > 1 && child == node )
		child = child->right;
	node->remove();
}

void FNode::subplot(ofstream &file) const {
	if ( child )
	  file <<  payload << key  << " -> " << child->payload << child->key << " [style=dashed,color=red]\n";

	if ( parent )
		file  << payload << key << " -> "  << parent->payload << parent->key << " [style=dotted,color=blue]\n";

	file  << payload << key << " -> "  << right->payload << right->key << "\n";
	file  << payload << key << " -> "  << left->payload << left->key << " [color=green]\n";

	file << "{rank=same; "  << payload << key << " " << right->payload << right->key << "}\n";

	file << "{\n";
	if ( child )
		child->makePlot(file);
	file << "}\n";
}

void FNode::makePlot(ofstream &file) const {
	subplot(file);
	for ( FNode *node = right; node != this; node = node->right )
		node->subplot(file);
}



