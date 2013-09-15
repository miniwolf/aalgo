#include "FNode.h"
#include <math.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include "../Node.h"
using namespace std;


template <class T>
FNode<T>::FNode(int key, T payload){
	this->payload = payload;
	this->key = key;
	child = NULL;
	parent = NULL;
	left = this;
	right = this;
	rank = 0;
	marked = false;
}


template <class T>
void FNode<T>::insert(FNode<T> *node){
	if( !node ){
		return;
	}
	if(parent){
		parent->rank++;
	}
	FNode<T> *x = right;
	FNode<T> *y = node->left;
	right = node;
	node->left = this;
	node->parent = parent;
	x->left = y;
	y->right = x;
}


template <class T>
void FNode<T>::remove(){

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


template <class T>
void FNode<T>::addChild(FNode<T> *node){
	if(!node){
		return;
	}

	if (node->key < Node<T>::key){
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


template <class T>
void FNode<T>::removeChild(FNode<T> *node){
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

template <class T>
void FNode<T>::subplot(ofstream &file){
	if ( child ){
	  file <<  this->payload << this->key  << " -> " << child->payload << child->key << " [style=dashed,color=red] \n";
	}

	if ( parent ){
		file  << this->payload << this->key << " -> "  << parent->payload << parent->key << " [style=dotted,color=blue] \n";
	}

	file  << this->payload << this->key << " -> "  << right->payload << right->key << "\n";
	file  << this->payload << this->key << " -> "  << left->payload << left->key << " [color=green] \n";

	file << "{rank=same; "  << this->payload << this->key << " " << right->payload << right->key << "}\n";

	file << "{ \n";
	if ( child ){
		child->makePlot(file);
	}
	file << "} \n";
}


