//#include "BinaryHeap.h"


BNode* BinaryHeap::insert(BNode* node){
  node->clear();

  if(size == 1){
    root = node;
    return node;
  }
  BoolArrayPointerTuple t = createTuple(size);
  root->insert(node, t.arr, t.counter);
  last = node;  
  BNode* l;
  
  
  if(l = node->balance()){
    last = l;
    while(node->balance());
  }
  
  if(!node->parent){
    root = node;
  }

  return node;
}

BoolArrayPointerTuple BinaryHeap::createTuple(int size){
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
