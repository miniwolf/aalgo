#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
using namespace std;

template <class T>
class Heap{
 public:
  virtual Node<T>* insert(int key, T payload)  = 0;
  virtual Node<T>* findMin() = 0;
  virtual Node<T>* deleteMin() = 0;
  virtual void decreaseKey(Node<T>* node, int key) = 0;
  void makePlot(string filename){   
    ofstream file;
    string fname = filename+".gv";
    file.open(fname.c_str());
    file << "digraph G {\n";
    Node<T>* n = findMin();
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
