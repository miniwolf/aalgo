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
    protected:
    private:
};

#endif // REDBLACK_H
