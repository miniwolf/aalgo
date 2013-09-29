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
  FNode<T> *left = this;
  FNode<T> *right = this;
  FNode<T> *parent = NULL;
  FNode<T> *child = NULL;

  bool marked  = false;
  int rank = 0 ;

  FNode(int key_, T payload_)
	:Node<T>(key_,payload_){
  assert(child == NULL);
  assert(parent == NULL);
}

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
      if ( parent->rank == 1 ){
        parent->child = NULL;
      } else {
        assert(parent->child != this);
      }
      parent->rank--;
      parent = NULL;
    }
    left->right = right;
    right->left = left;
    left = right = this;
  }

  void addChild(FNode<T> *node) {
    assert(this != node);
    assert(node);

    if ( node->key < Node<T>::key ) {
      cout << "Can not add child with smaller key " << endl;
      exit(1);
    }

    if ( child ){
      assert(this->rank > 0);
      child->insert(node);
    } else {
      assert(this->rank == 0);
      child = node;
      rank = 1;
    }

    node->parent = this;

    //children should not be marked when added
    node->marked = false;
    assert(node->parent == this);
  }

  bool knows(FNode<T>* node){
    assert(this->child != this);

    if( node == parent || node == child || node == right || node == left){
        return true;
    }

    if ( child ){
        if(child->knows(node)){
            return true;
        }
    }

    if(right != this){
        assert(right->left == this);
        FNode<T>* temp = right;
        while(temp != this){
            if( node == temp->parent||
                node == temp->child ||
                node == temp->right ||
                node == temp->left){
                return true;
            }
            if(temp->child){
                assert(temp->child->parent == temp);
                if(temp->child->knows(node)){
                    return true;
                }
            }
            assert(temp->right->left == temp);
            assert(temp != temp->right);
            temp = temp->right;
        }
    }
     return false;
  }

  void removeChild(FNode<T> *node) {
    assert(node);
    assert(this->rank > 0);
    assert(node->parent == this);

    // there are other children left
    if ( rank > 1 && child == node ){
      assert(child != child->right);
      child = child->right;
      assert(child->parent == this);
    }

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

  virtual ~FNode(){
    assert(left == this);
    assert(right == this);
    assert(parent == NULL);
    assert(child == NULL);
  }

};

#endif
