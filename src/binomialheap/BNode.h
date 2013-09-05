#ifndef BNODE_H_
#define BNODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class BNode {
 public:
  int key;
  string payload;
  
  BNode* parent;
  BNode* left; 
  BNode* right;
  
  void makePlot(ofstream &file);
}
#endif
