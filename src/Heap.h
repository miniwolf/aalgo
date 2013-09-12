#ifndef HEAP_H_
#define HEAP_H_
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
using namespace std;

class Heap{
 public:
  virtual Node* insert(int key, string payload)  = 0;
  virtual Node* findMin() = 0;
  virtual Node* deleteMin() = 0;
  virtual void decreaseKey(Node* node, int key) = 0;
  void makePlot(string filename){   
    ofstream file;
    string fname = filename+".gv";
    file.open(fname.c_str());
    file << "digraph G {\n";
    Node* n = findMin();
    if( n ){
      n->makePlot(file);
    }
    file << "}\n" << endl;
    file.close();
    string fname2 = filename;
    string arg = "dot -Tps " + fname2 + ".gv -o "+fname2+".ps";
    system(arg.c_str());
  }

  
  
};


#endif
