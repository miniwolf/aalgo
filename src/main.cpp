#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "test/TestPerformance.h"
#include "binary/BinaryHeap.h"

string IntToString(int num)
{     ostringstream myStream; //creates an ostringstream object
	  myStream<<num<<flush;
	  /*outputs the number into the string stream and then flushes
	  the buffer (makes sure the output is put into the stream)*/
	  return myStream.str(); //returns the string form of the stringstream object
}
using namespace std;

int main(int argc, char *argv[]){

  Heap* h = new BinaryHeap();
  h->insert(2, "p");
  h->insert(3, "p");  
  h->insert(4, "p");
  h->insert(5, "p");
  h->insert(6, "p");  
  h->insert(7, "p");
  h->insert(8, "p");
  h->insert(9, "p");  
  h->insert(10, "p");
  h->insert(11, "p");
  h->insert(12, "p");  
  // h->insert(1, "b");
  h->deleteMin();
  h->makePlot("graphs/g0");
  
}


