#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include "../Heap.h"
#include "BNode.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


using namespace std;

struct BoolArrayPointerTuple{
  bool* arr;  
  int counter;
};


class BinaryHeap : public Heap{
  
 private:
  int size = 0;
  BNode* root = NULL;
  BNode* last = NULL;
  void deleteAndInsert(BNode* n);
  BNode* insert(BNode* n);
  BoolArrayPointerTuple createTuple(int size);

 public:
  BinaryHeap(){}
  
  virtual BNode* insert(int key, string payload){
    BNode* node = new BNode(key, payload);
    size++;
    insert(node);
  }
  
  virtual BNode* findMin(){
    return root;
  }
  virtual BNode* deleteMin(){
    if(!size){
      return NULL;
    } 
    size--;
    if(last->parent->lChild == last){
      last->parent->lChild = NULL;
    } else if (last->parent->rChild == last){
      last->parent->rChild = NULL;
    }
    BNode* r = root, *lp;
    root = last;
    last->lChild = r->lChild;
    last->rChild = r->rChild;
    if(r->lChild){
      r->lChild->parent = last;
    }
    if(r->rChild){
      r->rChild->parent = last;
    }
    last->parent = NULL;

    BNode* tempN = NULL;
    bool first = true;
    do {
      if(last->rChild && last->lChild){      
	if(last->rChild->key < last->lChild->key){
	  tempN = last->rChild->balance();
	} else {
	  tempN = last->lChild->balance();
	}
      } else if(last->lChild){
	tempN = last->lChild->balance();
      } else if(last->rChild) {
	tempN = last->rChild->balance();
      } else {
	tempN = NULL;
      }
      if(first && tempN){
	first = false;
	root = tempN->parent;
      }	
    } while(tempN);

    BoolArrayPointerTuple t = createTuple(size);
    last = root->find(t.arr, t.counter);
    r->clear();
    return r;
  }

  virtual void decreaseKey(Node* node, int key){ }

  virtual void decreaseKey(BNode* node, int key){    
    node->key = key;
    if(node == root){
      return;
    }
    node->balance();
    if(!node->parent){
      root = node;
    }
  }
  
  
};

#endif
