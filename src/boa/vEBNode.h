#ifndef VEBNODE_H
#define VEBNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Node.h"
using namespace std;

template <class T>
class vEBNode : public Node<T>{
public:
    vEBNode(int key) : Node<T>(key, 0){}

  virtual void makePlot(ofstream &) {

    }

};

#endif
