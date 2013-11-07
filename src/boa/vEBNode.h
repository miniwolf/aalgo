#ifndef FNODE_H
#define FNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Node.h"
using namespace std;

template <class T>
class vEBNode : public Node<T>{
public:
    vEBNode(int key) : Node<T>(key, NULL){}

  virtual void makePlot(ofstream &file) {

    }

};

#endif
