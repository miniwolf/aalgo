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

void RedBlack::insertFixup(RBNode *z){
    while(z->p->color == RED){
        if(z->p == z->p->p->left){
            RBNode* y = z->p->p->right;
            if (y->color == RED){
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if(z == z->p->right){
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
            }
        } else {
           RBNode* y = z->p->p->left;
            if (y->color == RED){
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if(z == z->p->left){
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
    }
    root->color = BLACK;
}
