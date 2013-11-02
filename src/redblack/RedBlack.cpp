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
