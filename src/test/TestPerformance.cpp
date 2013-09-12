#include "TestPerformance.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

void TestPerformance::testInsert(int num_insertions){
  for(int i = 0;  i< num_insertions; i++){
    mHeap->insert(i, "Payload");
  }
}

void TestPerformance::testDeleteMin(int num_deletions){
  for(int i = 0;  i< num_deletions; i++){
    mHeap->deleteMin();
  }
  
}

void TestPerformance::testDecreaseKey(Node* node, int step, int num_decreasions){
  
}

void TestPerformance::startClock(){
  mStartTime = getTime();
}

double TestPerformance::stopClock(){
  return (getTime()) - mStartTime; 
}

double TestPerformance::getTime(){
  timeval tv;
  gettimeofday (&tv, NULL);
  return double (tv.tv_sec) + 0.000001 * tv.tv_usec;
}
