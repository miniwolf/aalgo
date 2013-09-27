#ifndef FNODE_H
#define FNODE_H

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

  FNode(int key_, T payload_)
	:Node<T>(key_,payload_),
    child(NULL),
    parent(NULL),
    left(this),
    right(this),
    rank(0),
    marked(false){}

  //void insert(FNode<T> *node);
  void insert(FNode<T> *node){
	if ( !node )
      return;
    if ( parent )
      parent->rank++;

    right->left = node->left;
    node->left->right = right;
    right = node;
    node->left = this;    
    node->parent = parent;
  }

  void remove() {
    if ( parent ) {
      if ( parent->rank == 1 )
        parent->child = NULL;
      parent->rank--;
      parent = NULL;
    }
    left->right = right;
    right->left = left;
    left = right = this;
  }
	
  void addChild(FNode<T> *node) {
    assert(node);

    if ( node->key < Node<T>::key ) {
      cout << "Can not add child with smaller key " << endl;
      exit(1);
    }

    if ( child )
      child->insert(node);
    else
      child = node;

    node->parent = this;
    rank++;
  
    //children should not be marked when added
    node->marked = false;
  }

  void removeChild(FNode<T> *node) {
    assert(node);
	
    if ( node->parent != this ) {
      cout << "Removing child whos parent we not are" << endl;
      exit(1);
    }
	
    // there are other children left
    if ( rank > 1 && child == node )
      child = child->right;
    node->remove();
  }

  void subplot(ofstream &file){
    if ( child )
      file <<  this->payload << this->key  << " -> " << child->payload << child->key << " [style=dashed,color=red] \n";

    if ( parent )
      file  << this->payload << this->key << " -> "  << parent->payload << parent->key << " [style=dotted,color=blue] \n";

    file  << this->payload << this->key << " -> "  << right->payload << right->key << "\n";
    file  << this->payload << this->key << " -> "  << left->payload << left->key << " [color=green] \n";
    file << "{rank=same; "  << this->payload << this->key << " " << right->payload << right->key << "}\n";
    file << "{ \n";
    if ( child )
      child->makePlot(file);
    file << "} \n";
  }
  
  virtual void makePlot(ofstream &file) {
    subplot(file);

    FNode *temp = right;

    while(!(temp == this)){
      temp->subplot(file);
      temp = temp->right;
    }
  }

  ~FNode(){}

};

#endif
