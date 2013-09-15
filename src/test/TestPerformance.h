
#ifndef TESTPERFORMANCE_H_
#define TESTPERFORMANCE_H_
#include "../Heap.h"

class TestPerformance {
 private:
  Heap<string>* mHeap;
  long double mStartTime;
  double getTime();
 public:
  TestPerformance(Heap<string>* h){
    mHeap = h;
    mStartTime = 0;
  }
  void testInsert(int num_insertions);
  void testDeleteMin(int num_deletions);
  void testDecreaseKey(Node<string>* node, int step, int num_decreasions);
  void startClock();
  double stopClock();
};

#endif /* TESTFIBHEAP_H_ */
