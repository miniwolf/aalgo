#ifndef BNODE_H
#define BNODE_H

#include "../Node.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class BNode : public Node{  
 public:
  BNode(int key, string payload) {
    this->key = key;
    this->payload = payload;
  }

  void insert(BNode* node, bool* direction, int startIndex);
  BNode* parent = NULL;
  BNode* lChild = NULL;
  BNode* rChild = NULL;
  virtual void makePlot(ofstream &file) {
    if ( lChild )
      file << payload << key << " -> " << lChild->payload << lChild->key << "[color=red] \n";
    if (rChild)
      file << payload << key << " -> " << rChild->payload << rChild->key << "[color=blue] \n";

    if ( rChild && lChild )
      file << "{rank=same; " << lChild->payload << lChild->key << " " << rChild->payload << rChild->key << "}\n";

    file << "{ \n";
    if ( lChild )
      lChild->makePlot(file);
    if ( rChild )
      rChild->makePlot(file);
    file << "} \n";
  }
};


#endif
