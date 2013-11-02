#ifndef REDBLACK_H
#define REDBLACK_H

#include "RBNode.h"

/**
 * This implementation is based on CLRS Chapter 13.
 *
 */
class RedBlack
{
    public:
        RBNode* NIL;
        RBNode* root = NULL;
        const bool RED = false;
        const bool BLACK = true;
        RedBlack();
        virtual ~RedBlack();
        RBNode* treeSearch(RBNode* x, int k);
        RBNode* minimum(RBNode* x);
        RBNode* maximum(RBNode* x);
        RBNode* successor(RBNode* x);
        RBNode* predecessor(RBNode* x);
        RBNode* insert(int key);
    protected:
    private:
        void leftRotate(RBNode* x);
        void rightRotate(RBNode* x);
        void insertFixup(RBNode* z);
        void insertNode(RBNode* z); // CLRS insert page 315
        void transplant(RBNode* u, RBNode* v);
        void deleteFixup(RBNode* x);
        void remove(RBNode* z);
    };

#endif // REDBLACK_H
