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

int RedBlack::treeSearch(RBNode* x, int k){
    while (x != NIL and k != x->key){
        if( k < x->key ) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

RBNode* RedBlack::minimum(RBNode* x){
    while ( x->left != nil){
        x = x->left;
    }
    return x;
}

RBNode* RedBlack::maximum(RBNode* x){
    while ( x->right != nil){
        x = x->right;
    }
    return x;
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

void RedBlack::insertNode(RBNode* z){
    RBNode* y = NIL;
    RBNode* x = root;
    while (x != NIL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NIL){
        root = z
    } else if (x->key < y->key){
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->color = RED;
    insertFixup(z);
}

void RedBlack::transplant(RBNode* u, RBNode* v){
    if (u->p == NIL){
        root = v;
    } else if( u == u->p->left){
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    v->p = u->p;
}

void RedBlack::remove(RBNode z*){
    RBNode* y = z;
    bool yOriginalColor = y->color;
    if(z->left == NIL){
        RBNode* x = z->right;
        transplant(z,z->right);
    } else if(z->right == NIL){
        x = z->left;
        transplant(z,z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->p == z){
            x->p = y;
        } else {
            transplant(y,y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK){
        deleteFixup(x);
    }
}

void RedBlack::deleteFixub(RBNode* x){
    while( x != root and x->color == BLACK){
        if (x == x->p->left){
            RBNode* w = x->p->right;
            if (w->color == RED){
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK and w->right->color == BLACK){
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->p);
                x = root;
            }
        } else {
            RBNode* w = x->p->left;
            if (w->color == RED){
                w->color = BLACK;
                x->p->color = RED;
                rightRotate(x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK and w->left->color == BLACK){
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->p);
                x = root;
            }
        }
    }
    x->color = BLACK;
}
