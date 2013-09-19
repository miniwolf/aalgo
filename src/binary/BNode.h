#ifndef BNODE_H_
#define BNODE_H_

#include "../Node.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <class T> 
class BNode : public Node<T>{  
 public:
 BNode(int key, T payload) : Node<T>(key, payload){}
  
  BNode<T>* parent = NULL;
  BNode<T>* lChild = NULL;
  BNode<T>* rChild = NULL;
  virtual void makePlot(ofstream &file){
    if (lChild) {
      file << this->payload << this->key << " -> " << lChild->payload << lChild->key << "[color=red] \n";
    }

    if (rChild) {
      file << this->payload << this->key << " -> " << rChild->payload << rChild->key << "[color=blue] \n";
    }
    if (parent) {
      file << this->payload << this->key << " -> " << parent->payload << parent->key << "[color=green] \n";
    }

    if ( rChild && lChild ){
      file << "{rank=same; " << lChild->payload << lChild->key << " " << rChild->payload << rChild->key << "}\n"; 
    }

    file << "{ \n";
    if(lChild){
      lChild->makePlot(file);
    }
    if(rChild){
      rChild->makePlot(file);
    }
    file << "} \n";
  }

void insert(BNode<T>* node, bool* direction, int startIndex){
  
  if(!lChild){
    node->parent = this;
    lChild = node;
    return;
  }
  if(!rChild){
    node->parent = this;
    rChild = node;
    return;
  }
  
  if(direction[startIndex]){
    rChild->insert(node, direction, ++startIndex);    
  } else {
    lChild->insert(node, direction, ++startIndex);      
  }
  
}

 BNode<T>* find(bool* direction, int startIndex){
  
   if(!lChild && !rChild){
     return this;
   }
   if(direction[startIndex]){
     return rChild->find(direction, ++startIndex);
   } else {
     return lChild->find(direction, ++startIndex);  
   }
 }



 BNode<T>* balance(){
   if(!parent || parent->key<=this->key){
     return NULL;
   }

   BNode<T>* p = parent, *op = parent->parent, *orc = parent->rChild, *olc = parent->lChild; 
   if(op){
     if(op->lChild == parent){
       op->lChild = this;
     } else {
       op->rChild = this;
     }
   }
  

   parent->parent = this;
   parent->lChild = lChild;
   parent->rChild = rChild;
   parent = op; 
   if(lChild){
     lChild->parent = p;
   }
   if(rChild){
     rChild->parent = p;
   }
  
   if(olc == this){
     rChild = orc;
     lChild = p;
     if(orc){
       orc->parent = this;
     }
   } else if (orc == this) {
     if(olc){
       olc->parent = this;
     }
     rChild = p;
     lChild = olc;
   }
  
   return p;
 }


 void clear(){
   parent = lChild = rChild = NULL;
 }


};


#endif
