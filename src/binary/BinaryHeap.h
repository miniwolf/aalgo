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

template <class T>

class BinaryHeap : public Heap<T>{
  
 private:
  int size = 0;
  BNode<T>* root = NULL;
  BNode<T>* last = NULL;
  void deleteAndInsert(BNode<T>* n);

 public:
 BinaryHeap():Heap<T>(){}
  
  virtual BNode<T>* insert(int key, T payload){
    BNode<T>* node = new BNode<T>(key, payload);
    size++;
    insert(node);
  }
  
  virtual BNode<T>* findMin(){
    return root;
  }
  virtual BNode<T>* deleteMin(){
    if(!size){
      return NULL;
    } 
    size--;
    if(root == last){
      BNode<T>* tn = last;
      root = last = NULL;
      return tn;
    }
    
    if(last->parent->lChild == last){
      last->parent->lChild = NULL;
    } else if (last->parent->rChild == last){
      last->parent->rChild = NULL;
    }
    BNode<T>* r = root, *lp;
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

    BNode<T>* tempN = NULL;
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

  virtual void decreaseKey(Node<T>* node, int key){ }

  virtual void decreaseKey(BNode<T>* node, int key){    
    node->key = key;
    if(node == root){
      return;
    }
    node->balance();
    if(!node->parent){
      root = node;
    }
  }
  
  
  BNode<T>* insert(BNode<T>* node){
    node->clear();

    if(size == 1){
      root = node;
      return node;
    }
    BoolArrayPointerTuple t = createTuple(size);
    root->insert(node, t.arr, t.counter);
    last = node;  
    BNode<T>* l;
  
  
    if(l = node->balance()){
      last = l;
      while(node->balance());
    }
  
    if(!node->parent){
      root = node;
    }

    return node;
  }

 BoolArrayPointerTuple createTuple(int size){
   int n = size, i = 0, arSize = ceil(log2(size))+1;
   bool boolAr[arSize];
   while(n != 0){
     i++;      
     boolAr[arSize-i] = (n % 2) == 1;
    n = n/2;
   }
   
   BoolArrayPointerTuple t;
   t.arr = boolAr;
   t.counter = arSize-i+1;
   return t;
 }

};

#endif
