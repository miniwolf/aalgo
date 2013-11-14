#include <asm/unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include "PerformSearches.h"
#include "../redblack/RedBlack.h"
#include "../boa/vEB.h"
#include "../timespec/timespec.h"

using namespace std;

struct perf_event_attr pe;

PerformSearches::PerformSearches(){}

PerformSearches::~PerformSearches(){}

long perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags){
    return syscall(__NR_perf_event_open, hw_event, pid, cpu,
                   group_fd, flags);
}

int testPageFaults() {
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_SOFTWARE;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = PERF_COUNT_SW_PAGE_FAULTS;
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;

    int fd = perf_event_open(&pe, 0, -1, -1, 0);
    if ( fd == -1 ) {
       fprintf(stderr, "Error opening leader %llx\n", pe.config);
       exit(EXIT_FAILURE);
    }
    return fd;
}

void resetEnableFD(int fd) {
    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
}

long long disableCount(int fd) {
    long long count;

    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
    read(fd, &count, sizeof(long long));
    return count;
}

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

    int fd = testPageFaults();
    resetEnableFD(fd);

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        rbInOrder->predecessor(i);
    }
    times[0] = stopClock();
    times[2] = double(disableCount(fd));

    resetEnableFD(fd);

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        vbInOrder->predecessor(i);
    }
    times[1] = stopClock();
    times[3] = double(disableCount(fd));

    close(fd);

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

    double* times = new double[4];

    for ( int i = 0; i < half_universe; i++ ) {
        rbInserted[i] = rbInOrder->insert(ordered[i]);
        vbInOrder->insert(ordered[i]);
    }

    int fd = testPageFaults();
    resetEnableFD(fd);

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        rbInOrder->member(i);
    }
    times[0] = stopClock();
    times[2] = double(disableCount(fd));

    resetEnableFD(fd);
    startClock();
    for ( int i = 0; i < universe; i++ ) {
       vbInOrder->member(i);
    }
    times[1] = stopClock();
    times[3] = double(disableCount(fd));
    close(fd);

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

    double* times = new double[4];

    for ( int i = 0; i < universe; i++ ) {
        rbInserted[i] = rbInOrder->insert(ordered[i]);
        vbInOrder->insert(ordered[i]);
    }

    shuffle(ordered,universe);

//    int fd = testPageFaultsReset();

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        rbInOrder->remove(rbInserted[i]);
    }
    times[0] = stopClock();

//    times[2] = double(testPageFaultsDisable(fd));

//    fd = testPageFaultsReset();

    startClock();
    for ( int i = 0; i < universe; i++ ) {
        vbInOrder->remove(ordered[i]);
    }
    times[1] = stopClock();

//    times[3] = double(testPageFaultsDisable(fd));

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
    RedBlack* rbShuffle = new RedBlack();
    RedBlack* rbInOrder = new RedBlack();
    vEB* vbShuffle = new vEB(universe);
    vEB* vbInOrder = new vEB(universe);

    int* shuffled = makeSet(universe);
    int* ordered  = makeSet(universe);
    shuffle(shuffled,universe);

    double* times = new double[8];

//    int fd = testPageFaultsReset();
    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        rbShuffle->insert(shuffled[i]);
    }
    times[0] = stopClock();
//    times[4] = double(testPageFaultsDisable(fd));

//    fd = testPageFaultsReset();
    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        rbInOrder->insert(ordered[i]);
    }
    times[1] = stopClock();
//    times[5] = double(testPageFaultsDisable(fd));

//    fd = testPageFaultsReset();
    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        vbShuffle->insert(shuffled[i]);
    }
    times[2] = stopClock();
//    times[6] = double(testPageFaultsDisable(fd));

//    fd = testPageFaultsReset();
    startClock();
    for ( int i = 0; i < universe ; i++ ) {
        vbInOrder->insert(ordered[i]);
    }
    times[3] = stopClock();
//    times[7] = double(testPageFaultsDisable(fd));

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
