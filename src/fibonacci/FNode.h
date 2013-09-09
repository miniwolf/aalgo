#ifndef FNODE_H
#define FNODE_H

#include <iostream>
#include <string>

class FNode {
public:
  FNode(int key, std::string payload);
  void insert(FNode *node);
  void remove();
  void addChild(FNode *node);
  void removeChild(FNode *node);
  void subplot(std::ofstream &file) const;
  void makePlot(std::ofstream &file) const;

public:
  std::string payload;
  FNode *left;
  FNode *right;
  FNode *parent;
  FNode *child;
  int rank;
  int key;
  bool marked;

};

#endif
