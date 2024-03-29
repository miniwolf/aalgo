#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include "../Heap.h"
#include "BNode.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


using namespace std;


struct BoolArrayPointerTuple{
  bool* arr;
  int counter;
};

template <class T>

class BinaryHeap : public Heap<T>{

 private:
  int size = 0;
  int counter = 0;
  int comparisons;
  BNode<T>* root = NULL;
  BNode<T>* last = NULL;
  void deleteAndInsert(BNode<T>* n);

 public:
 BinaryHeap():Heap<T>(){}
 virtual ~BinaryHeap(){
    if(root){
      //cout << "Leftovers in BinaryHeap!" <<  "  size: "<< size << endl;
      delete root;
    }
 }

 virtual int getComparisons(){
    return comparisons;
 }

  virtual int getSize() {
    return size;
  }

  virtual BNode<T>* insert(int key, T payload){
    BNode<T>* node = new BNode<T>(key, payload);
    size++;
    return insert(node);
  }

  virtual BNode<T>* findMin(){
    return root;
  }

  virtual BNode<T>* deleteMin(){
    //BoolArrayPointerTuple ta = createTuple(size);
    //last = root->find(ta.arr, ta.counter);

    /*cout << last->key << endl;
    cout << size << endl;*/

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
    BNode<T>* r = root;
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
    /*cout << "array: " << "t.counter: " <<  t.counter << endl;
    for( int ij = 0 ; ij < t.counter ; ij++){
      cout << t.arr[ij] << endl;
    }*/

    last = root->find(t.arr, t.counter);
    r->clear();

    delete [](t.arr);
    return r;
  }

  virtual void decreaseKey(Node<T>* node, int key){
    decreaseKey(dynamic_cast<BNode<T>*> (node), key);
  }

  virtual void decreaseKey(BNode<T>* node, int key){
    assert( key <= node->key);
    node->key = key;
    if(node == root){
      return;
    }

    if(node==last){
        BNode<T>* temp = node->balance();
        if(temp){
            last = temp;
        }
    }
    while(node->balance());

    if(!node->parent){
      root = node;
    } else {
      assert(node->parent->key <= node->key);
    }
  }


  BNode<T>* insert(BNode<T>* node){
    comparisons = 0;
    node->clear();

    if(size == 1){
      root = node;
      return node;
    }
    BoolArrayPointerTuple t = createTuple(size);
    root->insert(node, t.arr, t.counter);
    last = node;
    BNode<T>* l;

    if((l = node->balance())){
      last = l;
      comparisons++;
      while(node->balance()){
        comparisons++;
      };
    }

    if(!(node->parent)){
      root = node;
    }


    delete [](t.arr);
    return node;
  }

template<class C>
int integer_log2(C t){
  C result = 0;
  while(t){
    result++;
    t/=2;
  }
  return result;
}

BoolArrayPointerTuple createTuple(int size){
  int n = size;
  int arSize = sizeof(size)*8; // antal bytes gange 8 = antal bits.

  bool* boolAr = new bool[arSize];

  for(int i = 0 ; i < arSize ; i++ ){
    boolAr[i] = false;
  }

  int i=0;
  while(n != 0){
    boolAr[arSize -1 -i] = (n % 2) == 1;
    n = n/2;
    i++;
  }

  BoolArrayPointerTuple t;
  t.arr = boolAr;
  t.counter = arSize-i+1;
  return t;
}

 virtual void remove(Node<T>* n){
   remove(dynamic_cast<BNode<T>*> (n));
 }

 virtual void remove(BNode<T>* n){
   decreaseKey(n, root->key-1);
   deleteMin();
 }
};

#endif
