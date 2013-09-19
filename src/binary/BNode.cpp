#include "BNode.h"


void BNode::insert(BNode* node, bool* direction, int startIndex){
  
  if(!lChild){
    node->parent = this;
    lChild = node;
    return;
  }
  if(!rChild){
    node->parent = this;
    rChild = node;
    return;
  }
  
  if(direction[startIndex]){
    rChild->insert(node, direction, ++startIndex);    
  } else {
    lChild->insert(node, direction, ++startIndex);      
  }
  
}

BNode* BNode::find(bool* direction, int startIndex){
  
  if(!lChild && !rChild){
    return this;
  }
  if(direction[startIndex]){
    return rChild->find(direction, ++startIndex);
  } else {
    return lChild->find(direction, ++startIndex);  
  }
}



BNode* BNode::balance(){
  if(!parent || parent->key<=key){
    return NULL;
  }

  BNode* p = parent, *op = parent->parent, *orc = parent->rChild, *olc = parent->lChild; 
  if(op){
    if(op->lChild == parent){
      op->lChild = this;
    } else {
      op->rChild = this;
    }
  }
  

  parent->parent = this;
  parent->lChild = lChild;
  parent->rChild = rChild;
  parent = op; 
  if(lChild){
    lChild->parent = p;
  }
  if(rChild){
    rChild->parent = p;
  }
  
  if(olc == this){
    rChild = orc;
    lChild = p;
    if(orc){
      orc->parent = this;
    }
  } else if (orc == this) {
    if(olc){
      olc->parent = this;
    }
    rChild = p;
    lChild = olc;
  }
  
  return p;
}


void BNode::clear(){
  parent = lChild = rChild = NULL;
}
