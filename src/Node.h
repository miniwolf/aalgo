#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class Node {
 public:
  int key;
  string payload;
  virtual void makePlot(ofstream &file) = 0;
  
};

#endif
