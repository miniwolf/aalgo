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
  string ffilename = "test_f_file.csv", bfilename = "test_b_file.csv";
  ffile.open(ffilename.c_str());
  bfile.open(bfilename.c_str());
  for(int size = 10; size<=10000000  ; size = size*10){
    //cout << size << endl;
    for(int i = 0; i<50; i++){
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
  delete tPerf;
}

void testWorstPerformance(){
  TestPerformance* tPerf = new TestPerformance();
  ofstream ffile, bfile;
  string ffilename = "test_worst_f_file.csv", bfilename = "test_worst_b_file.csv";
  ffile.open(ffilename.c_str());
  bfile.open(bfilename.c_str());
  for(int size = 10; size<=10000000  ; size = size*10){
    //cout << size << endl;
    for(int i = 0; i<50; i++){
      Heap<int>* bHeap = new BinaryHeap<int>();
      Heap<int>* fHeap = new FibonacciHeap<int>();
      ffile << size << ", ";
      bfile << size << ", ";
      tPerf->performWorstTest(fHeap, size, ffile);
      tPerf->performWorstTest(bHeap, size, bfile);
      ffile << endl;
      bfile << endl;
      ffile.flush();
      bfile.flush();
      delete fHeap;
      delete bHeap;
    }
  }
  ffile.close();
  bfile.close();
  delete tPerf;
}

void testFib() {
  TestFibHeap *test = new TestFibHeap();
  assert(test->testFib());
}

void testNTagram(){
  ofstream file;
  string filename = "k_graph.csv";
  file.open(filename.c_str());

  int minSize = 10;
  int maxSize = 12000;
  int step = 2;


  TestPerformance* tPerf = new TestPerformance();
  for( int size = minSize; size < maxSize; size = size*step){
    for(int i = 0; i < 10; i++)
      tPerf->testNTagramDijkstra(size,file);
    file.flush();
  }
  delete tPerf;
}

void performRandomGraphDijkstra(){
    ofstream ffile,bfile,dfile;
    string bfilename = "random_graph_binary.csv";
    string ffilename = "random_graph_fibonacci.csv";
    string decrease = "random_graph_decrease_key.csv";
    bfile.open(bfilename.c_str());
    ffile.open(ffilename.c_str());
    dfile.open(decrease.c_str());

    int minSize = 10;
    int maxSize = 12000;
    int step = 2;

    bfile << " , ";
    ffile << " , ";
    dfile << " , ";

    for( int i = minSize; i <=maxSize ; i = i*step){
      bfile << i << " , ";
      ffile << i << " , ";
      dfile << i << " , ";
    }

    bfile << endl;
    ffile << endl;
    dfile << endl;

    TestPerformance* tPerf = new TestPerformance();
    for( double density = 0.001; density < 1.1 ; density += 0.05){
        bfile << density << " , ";
        ffile << density << " , ";
        dfile << density << " , ";
        for( int size = minSize; size <= maxSize; size = size*step){
                cout << "Density: " << density << "  Size: " << size << endl;
                tPerf->performRandomGraph(size, density*size, 20, bfile, ffile, dfile);
        }
        bfile << endl;
        ffile << endl;
        dfile << endl;
        bfile.flush();
        ffile.flush();
        dfile.flush();
    }

    bfile.close();
    ffile.close();
    dfile.close();
    delete tPerf;
}

void computeRandomGraphDecreaseRelation(int average){
    ofstream file;
    string filename = "decrease_relation.csv";
    file.open(filename.c_str());

    int minSize = 10;
    int maxSize = 10000;
    int step = 5;

    file << " , ";
    for( int i = minSize; i <=maxSize ; i = i*step){
        file << i << ", ";
    }
    file << endl;

    TestPerformance* tPerf = new TestPerformance();

    for(float density = 0.01f ; density <= 1.000001f;){

        if(density < 0.5f){
            density*= 1.2f;
        }else{
            density+=0.1f;
        }

        file << density << ", " ;
        for( int i = minSize; i <= maxSize ; i = i*step){
            cout << "size: " << i << "   density: " <<density * (float(i))<< endl;
            tPerf->testRandomGraphDecreaseKey(i,density * (float(i)),average,file);
            file.flush();
        }
        file << endl;
    }
    file.flush();
    file.close();
    delete tPerf;
}

void performSingleInsertBHeap(){
    ofstream file;
    string filename = "binary_inserts.csv";
    file.open(filename.c_str());
    TestPerformance* tPerf = new TestPerformance();
    Heap<int>* heap = new BinaryHeap<int>();

    for( int i = 10 ; i <= 100000000 ; i*=10){
        tPerf->testSameSizeInsertions(heap,i,50,file);
    }
    delete tPerf;
    delete heap;
}


void performLayerInsertBHeap(){
    ofstream file;
    string filename = "binary_layer_inserts.csv";

    file.open(filename.c_str());

    TestPerformance* tPerf = new TestPerformance();

    int layers = 26;
    int repeats = 25;
    for(int l = 0; l < layers; l++){
        file << l << ", ";
    }
    file << endl;
    for(int r = 0; r < repeats ; r++){
        Heap<int>* heap = new BinaryHeap<int>();
        tPerf->performLayerInsert(heap,layers,file);
        delete heap;
    }

    delete tPerf;
}

void performSingleFileGraph(){
    ofstream file;

    string filename = "single_file_graph_dijkstra.csv";

    file.open(filename.c_str());

    int minSize = 10;
    int maxSize = 12000;
    int step = 2;

    int average = 10;

    TestPerformance* tPerf = new TestPerformance();

    for (int size = minSize ; size < maxSize ; size*=step){
        double* result = new double[3];

        for( int i = 0; i < average; i++){
            double* temp = tPerf->testDijkstraLukas(size);
            result[0]+=temp[0];
            result[1]+=temp[1];
            result[2]+=temp[2];
            delete [] temp;
        }
        result[0]/=average;
        result[1]/=average;
        result[2]/=average;

        file << size << ", " << result[0] << ", " << result[1] << ", " << result[2] << endl;
        file.flush();
    }
}

int main() {
    // cout << "Performing worst case performance test." << endl;
    // testWorstPerformance();
    // cout << "Performing layered insertions for Binary Heap" << endl;
    // performLayerInsertBHeap();
    // cout << "Performing singular insertions" << endl;
    // performSingleInsertBHeap();
    //computeRandomGraphDecreaseRelation(10);
    //cout << "Running dijkstra on random graphs." << endl;
    //performRandomGraphDijkstra();
    cout << "Running dijkstra on k-graphs." << endl;
    testNTagram();

   // cout << "Running dijkstra on single depth graphs" << endl;
    //performSingleFileGraph();



}
