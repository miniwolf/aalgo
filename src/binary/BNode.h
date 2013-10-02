#ifndef BNODE_H
#define BNODE_H

#include "../Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

template <class T>
class BNode : public Node<T>{
public:
  BNode(int key, T payload) : Node<T>(key, payload){}
  virtual ~BNode(){
    if(lChild){
        delete lChild;
    }

    if(rChild){
        delete rChild;
    }
  }

  BNode<T>* parent = NULL;
  BNode<T>* lChild = NULL;
  BNode<T>* rChild = NULL;
  virtual void makePlot(ofstream &file){
    if ( lChild )
      file <<  "a"<< this->payload << "a" << this->key << " -> " << "a"<<lChild->payload  << "a" << lChild->key << "[color=red] \n";

    if ( rChild )
      file << "a"<<this->payload << "a" << this->key << " -> " << "a"<<rChild->payload  << "a" << rChild->key << "[color=blue] \n";

    if ( parent )
      file << "a"<<this->payload  << "a" << this->key << " -> " << "a"<<parent->payload  << "a" << parent->key << "[color=green] \n";

    if ( rChild && lChild )
      file << "{rank=same; "  << "a"<<lChild->payload  << "a" << lChild->key << " " << "a"<<rChild->payload  << "a" << rChild->key << "}\n";

    file << "{ \n";
    if ( lChild )
      lChild->makePlot(file);

    if ( rChild )
      rChild->makePlot(file);
    file << "} \n";
  }

  void insert(BNode<T>* node, bool* direction, int startIndex) {
    if ( !lChild ) {
      node->parent = this;
      lChild = node;
      return;
    }

    if ( !rChild && lChild ) {
       node->parent = this;
       rChild = node;
       return;
    }

    if ( direction[startIndex] )
      rChild->insert(node, direction, ++startIndex);
    else
      lChild->insert(node, direction, ++startIndex);
  }

  BNode<T>* find(bool* direction, int startIndex) {
   /* cout << "inside find" << endl;
    cout << "l:" << lChild << endl;
    cout << "r:" << rChild << endl;*/
    assert( (rChild && lChild) || lChild || (!rChild && !lChild));
    if ( !lChild && !rChild )
      return this;

    if ( direction[startIndex])
      return rChild->find(direction, ++startIndex);
    else
      return lChild->find(direction, ++startIndex);
  }

  BNode<T>* balance() {
    assert( (rChild && lChild) || lChild || (!rChild && !lChild));
    if ( !parent || parent->key <= this->key )
      return NULL;

    BNode<T>* p = parent, *op = parent->parent, *orc = parent->rChild, *olc = parent->lChild;
    if ( op ) {
      if ( op->lChild == parent )
        op->lChild = this;
      else
        op->rChild = this;
    }

    parent->parent = this;
    parent->lChild = lChild;
    parent->rChild = rChild;
    parent = op;
    if ( lChild )
      lChild->parent = p;
    if ( rChild )
      rChild->parent = p;

    if ( olc == this ) {
      rChild = orc;
      lChild = p;
      if ( orc )
        orc->parent = this;
    } else if (orc == this) {
      if ( olc )
        olc->parent = this;
      rChild = p;
      lChild = olc;
    }

    assert( (rChild && lChild) || lChild || (!rChild && !lChild));
    return p;
  }


  void clear() {
    parent = lChild = rChild = NULL;
  }
};
#endif
