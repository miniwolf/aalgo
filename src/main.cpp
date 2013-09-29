#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "test/TestPerformance.h"
#include "binary/BinaryHeap.h"
#include "dijkstra/Vertex.h"
#include "dijkstra/Graph.h"
#include "test/TestFibHeap.h"
#include <cstdlib>

using namespace std;

string IntToString(int num) {
  ostringstream myStream;
  myStream << num << flush;
  return myStream.str();
}

void writeSetFile(int* set, int size){
    string afilename = "SET.txt";
    ofstream setfile;
    setfile.open(afilename.c_str());
    for( int a = 0; a < size ; a++ ) {
        setfile << set[a] << endl;
    }
    setfile.flush();
    setfile.close();
}

void testPerformance(){
  TestPerformance* tPerf = new TestPerformance();
  ofstream ffile, bfile;
  string ffilename = "test_f_file", bfilename = "test_b_file";
  ffile.open(ffilename.c_str());
  bfile.open(bfilename.c_str());
  for(int size = 1000; size<=10000; size = size+1){
    for(int i = 0; i<50; i++){
      cout << size << endl;
      Heap<int>* bHeap = new BinaryHeap<int>();
      Heap<int>* fHeap = new FibonacciHeap<int>();
      int* set = new int[size];
      tPerf->generateKeySet(size, set);

      ffile << size << ", ";
      bfile << size << ", ";
      tPerf->runTest(fHeap, size, set, ffile);
      tPerf->runTest(bHeap, size, set, bfile);
      ffile << endl;
      bfile << endl;
      ffile.flush();
      bfile.flush();
      delete []set;
      delete fHeap;
      delete bHeap;
    }
  }
  ffile.close();
  bfile.close();
}

void testFib() {
  TestFibHeap *test = new TestFibHeap();
  assert(test->testFib());
}

int main() {
  testPerformance();
 /*Heap<int>* bHeap = new BinaryHeap<int>();
  TestPerformance* tPerf = new TestPerformance();
  int size = 5;
  int* set = new int[size];
  set[0] = 1921513324;
  set[1] = 2006223736;
  set[2] = 1166238333;
  set[3] = 1980908868;
  set[4] = 1233045774;
  ofstream file;
  string a = "a";
  file.open(a.c_str());
  tPerf->runTest(bHeap, size, set, file);*/
}
