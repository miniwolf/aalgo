#include "RedBlack.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

RedBlack::RedBlack()
{
    // CĹRS Page 309
    NIL = new RBNode();
    NIL->color = BLACK;
    root = NIL;
}

RedBlack::~RedBlack()
{
    //dtor
}

void RedBlack::leftRotate(RBNode* x){
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NIL){
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NIL){
        root = y;
    } else if(x == x->p->left){
        x->p->right = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

void RedBlack::rightRotate(RBNode* x){
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != NIL){
        y->right->p = x;
    }
    y->p = x->p;
    if ( x->p == NIL){
        root = y;
    } else if (x == x->p->right){
        x->p->right = y;
    } else {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
}
