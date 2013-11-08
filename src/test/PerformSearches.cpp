#include "PerformSearches.h"
#include "../redblack/RedBlack.h"
#include "../boa/vEB.h"
#include "../timespec/timespec.h"

PerformSearches::PerformSearches(){}

PerformSearches::~PerformSearches(){}

void PerformSearches::shuffle(int* array, int size) {
    srand(time(NULL));
    for ( int i = size-1 ; i > 0 ; i-- ) {
        int j = rand() % (i+1);
        assert(0 <= j && j <= i);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int* PerformSearches::makeSet(int size) {
    int* a = new int[size];
    for ( int i = 0; i < size; i++ ) {
        a[i] = i;
    }
    return a;
}

double* PerformSearches::performPre(int universe) {
    RedBlack* rbInOrder = new RedBlack();
    vEB* vbInOrder = new vEB(universe);

    int* ordered = makeSet(universe);
    RBNode** rbInserted = new RBNode*[universe];

    double* times = new double[2];

    for ( int i = 0; i < universe; i++ ) {
        rbInserted[i] = rbInOrder->insert(ordered[i]);
        vbInOrder->insert(ordered[i]);
    }

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        rbInOrder->predecessor(i);
    }
    times[0] = stopClock();

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        vbInOrder->predecessor(i);
    }
    times[1] = stopClock();

    delete rbInOrder;
    delete vbInOrder;

    delete[] ordered;
    delete[] rbInserted;

    return times;
}

double* PerformSearches::performMember(int universe) {
    int half_universe = universe * 0.5;

    RedBlack* rbInOrder = new RedBlack();
    vEB* vbInOrder = new vEB(universe);

    int* ordered = makeSet(half_universe);
    RBNode** rbInserted = new RBNode*[half_universe];

    double* times = new double[2];

    for ( int i = 0; i < half_universe; i++ ) {
        rbInserted[i] = rbInOrder->insert(ordered[i]);
        vbInOrder->insert(ordered[i]);
    }

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        rbInOrder->member(i);
    }
    times[0] = stopClock();

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        vbInOrder->member(i);
    }
    times[1] = stopClock();

    delete rbInOrder;
    delete vbInOrder;

    delete[] ordered;
    delete[] rbInserted;

    return times;
}

double* PerformSearches::performRemoves(int universe) {
    RedBlack* rbInOrder = new RedBlack();
    vEB* vbInOrder = new vEB(universe);

    int* ordered = makeSet(universe);
    RBNode** rbInserted = new RBNode*[universe];

    double* times = new double[2];

    for ( int i = 0; i < universe; i++ ) {
        rbInserted[i] = rbInOrder->insert(ordered[i]);
        vbInOrder->insert(ordered[i]);
    }

    shuffle(ordered,universe);

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        rbInOrder->remove(rbInserted[i]);
    }
    times[0] = stopClock();

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        vbInOrder->remove(ordered[i]);
    }
    times[1] = stopClock();

    delete rbInOrder;
    delete vbInOrder;

    delete[] ordered;
    for ( int i = 0; i < universe; i++ ) {
        rbInserted[i]->left = NULL;
        rbInserted[i]->right = NULL;
        delete rbInserted[i];
    }
    delete[] rbInserted;

    return times;
}

double* PerformSearches::performInserts(int universe) {
    // insert
    RedBlack* rbShuffle = new RedBlack();
    RedBlack* rbInOrder = new RedBlack();
    vEB* vbShuffle = new vEB(universe);
    vEB* vbInOrder = new vEB(universe);

    int* shuffled = makeSet(universe);
    int* ordered  = makeSet(universe);
    shuffle(shuffled,universe);

    double* times = new double[4];

    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        rbShuffle->insert(shuffled[i]);
    }
    times[0] = stopClock();

    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        rbInOrder->insert(ordered[i]);
    }
    times[1] = stopClock();

    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        vbShuffle->insert(shuffled[i]);
    }
    times[2] = stopClock();

    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        vbInOrder->insert(ordered[i]);
    }
    times[3] = stopClock();

    delete rbShuffle;
    delete rbInOrder;
    delete vbInOrder;
    delete vbShuffle;

    delete[] shuffled;
    delete[] ordered;

    return times;
}

void PerformSearches::getTime() {
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mStartTime);
}

double PerformSearches::stopClock() {
  timespec currentTime;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &currentTime);

  timespec result = timespec_sub(currentTime, mStartTime);

  return double(result.tv_sec) + 0.000000001*double(result.tv_nsec);
}

void PerformSearches::startClock() {
  getTime();
}
