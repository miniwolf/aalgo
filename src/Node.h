#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

template <class T> 
class Node{
 public:
  int key;
  T payload;
  virtual void makePlot(ofstream &file) = 0;
  Node(int k, T p):key(k),payload(p){}  
};

#endif
