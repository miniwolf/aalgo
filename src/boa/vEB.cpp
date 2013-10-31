#include "vEB.h"

using namespace std;

vEB::vEB(int universe){
    u = universe;
    lsqr = lowerSquareRoot(universe);

    cluster = new vEB*[lsqr];
}
