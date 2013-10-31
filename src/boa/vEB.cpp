#include "vEB.h"

using namespace std;

vEB::vEB(int universe){
    // constructor derived from p. 546, CLRS
    u = universe;
    lsqr = lowerSquareRoot(universe);
    usqr = upperSquareRoot(universe);

    summary = new vEB(usqr);
    cluster = new vEB*[usqr];
    for ( int i = 0; i < usqr ; i++){
        cluster[i] = new vEB(lsqr);
    }
}
