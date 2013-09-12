
#ifndef TESTPERFORMANCE_H_
#define TESTPERFORMANCE_H_
#include "../Heap.h"

class TestPerformance {
 private:
  Heap* mHeap;
  long double mStartTime;
  double getTime();
 public:
  TestPerformance(Heap* h){
    mHeap = h;
    mStartTime = 0;
  }
  void testInsert(int num_insertions);
  void testDeleteMin(int num_deletions);
  void testDecreaseKey(Node* node, int step, int num_decreasions);
  void startClock();
  double stopClock();
};

#endif /* TESTFIBHEAP_H_ */
