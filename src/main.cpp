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
    setfile << "size "<< size << endl;

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
  for(int size = 1000; size<=10000000  ; size = size*10){
    for(int i = 0; i<50; i++){
      cout << size << endl;
      Heap<int>* bHeap = new BinaryHeap<int>();
      Heap<int>* fHeap = new FibonacciHeap<int>();
      int* keyset = new int[size];
      tPerf->generateKeySet(size, keyset);
      //writeSetFile(set,size);
      ffile << size << ", ";
      bfile << size << ", ";
      tPerf->runTest(fHeap, size, keyset, ffile);
      tPerf->runTest(bHeap, size, keyset, bfile);
      ffile << endl;
      bfile << endl;
      ffile.flush();
      bfile.flush();
      delete []keyset;
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

void testNTagram(){
  ofstream file;
  string filename = "ntagram";
  file.open(filename.c_str());

  TestPerformance* tPerf = new TestPerformance();
  for( int size = 10; size < 20000; size = size*2){
    for(int i = 0; i < 10; i++)
      tPerf->testNTagramDijkstra(size,file);
    file.flush();
  }

  delete tPerf;
}

void computeRandomGraphDecreaseRelation(int average){
    ofstream file;
    string filename = "decrease_relation.csv";
    file.open(filename.c_str());

    int minSize = 10;
    int maxSize = 100;
    int step = 2;

    file << " , ";
    for( int i = minSize; i <=maxSize ; i = i*step){
        file << i << ", ";
    }
    file << endl;

    TestPerformance* tPerf = new TestPerformance();

    for(float density = 0.1f ; density <= 1.0001f; density +=  0.1f){
        file << density << ", " ;
        for( int i = minSize; i <= maxSize ; i = i*step){
            cout << "size: " << i << "   density: " <<density * (float(i))<< endl;
            tPerf->testRandomGraphDecreaseKey(i,density * (float(i)),average,file);
            file.flush();
        }
        file << endl;
    }
    delete tPerf;
}

int main() {

    computeRandomGraphDecreaseRelation(1);
  /*
  TestPerformance* tPerf = new TestPerformance();
  GraphSource* gs = makeRandomGraph(10000,5);
  double* result = tPerf->testDijkstra(gs);

  delete gs->graph;
  delete gs;
  delete tPerf;
  delete []result;
  */
  //testNTagram();
  //testPerformance();
  //tPerf->testDijkstra(makeNtagramGraph(20));

}
