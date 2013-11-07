#ifndef VEB_H
#define VEB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cmath>
#include <bitset>

#define CUTOFF 8
using namespace std;

class vEB{
// we use -1 as NIL
public:
    int NIL = -1;
    int min = -1;
    int max = -1;
    int count = 0;
    int u = 0; // universe size
    int lsqr = 0; //lower square root
    int usqr = 0; //upper square root

    bool useBitset = false;

    bitset<CUTOFF>* bits = new bitset<CUTOFF>();

    vEB** cluster;
    vEB* summary;

    vEB(int universe);

    // page 546 CLRS

    double lowerSquareRoot(int v){
    // TODO implement integer power function
        return pow(2.0,floor(log2(v)/2));
    }

    double upperSquareRoot(int v){
        return pow(2.0,ceil(log2(v)/2));
    }

    int high(int x){
        return floor(x / lsqr);
    }

    int low(int x){
        return x % lsqr;
    }

    int index(int x, int y){
        return x*lsqr + y;
    }

    int minimum(){
        return min;
    }

    int maximum(){
        return max;
    }

    bool member(int x);
    int successor(int x);
    int predecessor(int x);
    void emptyInsert(int x);
    void insert(int x);
    void remove(int x);
    int deleteMin();
    void decreaseKey(int x, int target);

};

#endif
