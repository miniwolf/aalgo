#include <asm/unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include "binary/BinaryHeap.h"
#include "boa/vEBHeap.h"
#include "dijkstra/Graph.h"
#include "dijkstra/Vertex.h"
#include "test/PerformSearches.h"
#include "test/TestFibHeap.h"
#include "test/TestPerformance.h"
#include "main.h"

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

void testPerformance(int repeats){
    PerformSearches* pSearch = new PerformSearches();
    ofstream insert_testfile, remove_testfile, member_testfile, predec_testfile;
    string insert = "1_testinsert_tree_file.csv";
    string remove = "1_testremove_tree_file.csv";
    string member = "1_testmember_tree_file.csv";
    string predec = "1_testpredec_tree_file.csv";
    insert_testfile.open(insert.c_str());
    remove_testfile.open(remove.c_str());
    member_testfile.open(member.c_str());
    predec_testfile.open(predec.c_str());
    for ( int size = 64; size <= pow(2,25); size *= 2 ) {
        for ( int i = 0; i < repeats; i++ ) {
            insert_testfile << size << ", ";
            remove_testfile << size << ", ";
            member_testfile << size << ", ";
            predec_testfile << size << ", ";
//            double* insert_times = pSearch->performInserts(size);
//            double* remove_times = pSearch->performRemoves(size);
            double* member_times = pSearch->performMember(size);
//            double* predec_times = pSearch->performPre(size);
//            for ( int i = 0; i < 8; i++ ) {
//                insert_testfile << insert_times[i] << ", ";
            //           }
            for ( int i = 0; i < 4; i++ ) {
                //    remove_testfile << remove_times[i] << ", ";
                member_testfile << member_times[i] << ", ";
                // predec_testfile << predec_times[i] << ", ";
            }
            insert_testfile << endl;
            remove_testfile << endl;
            member_testfile << endl;
            predec_testfile << endl;
            insert_testfile.flush();
            remove_testfile.flush();
            member_testfile.flush();
            predec_testfile.flush();
//            delete[] insert_times;
//            delete[] remove_times;
            delete[] member_times;
//            delete[] predec_times;
        }
    }
    insert_testfile.close();
    remove_testfile.close();
    member_testfile.close();
    predec_testfile.close();
    delete pSearch;
}

void testWorstPerformance(){
  TestPerformance* tPerf = new TestPerformance();
  ofstream ffile, bfile, vfile;
  string ffilename = "test_worst_f_file.csv", bfilename = "test_worst_b_file.csv", vfilename = "test_worst_v_file.csv";
  ffile.open(ffilename.c_str());
  bfile.open(bfilename.c_str());
  vfile.open(vfilename.c_str());
  for(int size = 64; size<=pow(2, 20)  ; size = size*2){
    //cout << size << endl;
    for(int i = 0; i<25; i++){
      Heap<int>* bHeap = new BinaryHeap<int>();
      Heap<int>* fHeap = new FibonacciHeap<int>();
      Heap<int>* vebHeap = new vEBHeap<int>(size*2);
      ffile << size << ", ";
      bfile << size << ", ";
      vfile << size << ", ";
      tPerf->performWorstTest(fHeap, size, ffile);
      tPerf->performWorstTest(bHeap, size, bfile);
      tPerf->performWorstTest(vebHeap, size, vfile);
      ffile << endl;
      bfile << endl;
      vfile << endl;
      ffile.flush();
      bfile.flush();
      vfile.flush();
      delete fHeap;
      delete bHeap;
      delete vebHeap;
    }
  }
  ffile.close();
  bfile.close();
  vfile.close();
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

void performRandomGraphDijkstra2(){
    ofstream ffile,bfile,dfile;
    string bfilename = "random_graph_binary2.csv";
    string ffilename = "random_graph_fibonacci2.csv";
    string decrease = "random_graph_decrease_key2.csv";
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
    for( double density = 0.0001; density < 0.01 ; density += 0.001){
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
    testPerformance(5);
    //cout << "Performing worst case performance test." << endl;
    //testWorstPerformance();
}
