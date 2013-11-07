#include "RBNode.h"

RBNode::RBNode()
{
    color = true;
    key = 0;
    left = NULL;
    right = NULL;
    p = NULL;
}

RBNode::~RBNode()
{
    if ( left && left->key != -1 )
        delete left;
    if ( right && right->key != -1 )
        delete right;
}
