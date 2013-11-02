#ifndef RBNODE_H
#define RBNODE_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class RBNode
{
    public:
        bool color;
        int key;
        RBNode* left;
        RBNode* right;
        RBNode* p; //parent
        RBNode();
        virtual ~RBNode();
    protected:
    private:
};

#endif // RBNODE_H
