#include "vEB.h"

using namespace std;

/**
 * This implementation currently uses -1 as NIL, until we switch to an item-based
 * implementation, where items contain a key and a payload.
 */
vEB::vEB(int universe){
    // constructor derived from p. 546, CLRS
    min = NIL;
    max = NIL;
    u = universe;
    lsqr = lowerSquareRoot(universe);
    usqr = upperSquareRoot(universe);

    summary = new vEB(usqr);
    cluster = new vEB*[usqr];
    for ( int i = 0; i < usqr ; i++){
        cluster[i] = new vEB(lsqr);
    }

}

bool vEB::member(int x){
    assert(x > NIL);
    if (x == min or x == max){
        return true;
    } else if( u == 2 ){
        return false;
    } else {
        return cluster[high(x)]->member(low(x));
    }
}

int vEB::successor(int x){
    assert(x > NIL);
    if(u == 2){
        if ( x == 0 and max == 1 ){
            return 1;
        } else {
            return NIL;
        }
    } else if (min != NIL and x < min) {
        return min;
    } else {
        int maxLow = cluster[high(x)]->max;
        if ( maxLow != NIL and low(x) < maxLow){
            int offset = cluster[high(x)]->successor(low(x));
            return index(high(x),offset);
        } else {
            int succCluster = summary->successor(high(x));
            if ( succCluster == NIL){
                return NIL;
            } else {
                int offset = cluster[succCluster]->min;
                return index(succCluster,offset);
            }
        }
    }
}

int vEB::predecessor(int x){
    if( u == 2){
        if( x == 1 and min == 0){
            return 0;
        } else {
            return NIL;
        }
    } else if ( max != NIL and x > max){
        return max;
    } else {
        int minLow = cluster[high(x)]->min;
        if ( minLow != NIL and low(x) > minLow ){
            int offset = cluster[high(x)]->predecessor(low(x));
            return index(high(x),offset);
        } else {
            int predCluster = summary->predecessor((high(x)));
            if ( predCluster == NIL ){
                if ( min != NIL and x > min){
                    return min;
                } else {
                    return NIL;
                }
            } else {
                int offset  = cluster[predCluster]->max;
                return index(predCluster,offset);
            }
        }
    }
}
