#ifndef NODE_H
#define NODE_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <class T> 
class Node{
 public:
  int key;
  T payload;
  virtual void makePlot(ofstream &file) = 0;
  virtual ~Node(){};
  Node(int k, T p):key(k),payload(p){}  
};

#endif
