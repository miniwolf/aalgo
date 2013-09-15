#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "test/TestPerformance.h"
#include "binary/BinaryHeap.h"
#include "dijkstra/Vertex.h"
#include "dijkstra/Graph.h"

using namespace std;

string IntToString(int num)
{     ostringstream myStream; //creates an ostringstream object
	  myStream<<num<<flush;
	  /*outputs the number into the string stream and then flushes
	  the buffer (makes sure the output is put into the stream)*/
	  return myStream.str(); //returns the string form of the stringstream object
}


int main(int argc, char *argv[]){
	Vertex* n1 = new Vertex(1);
	Vertex* n2 = new Vertex(2);

	n1->addNeighbour(n2,10);

	Graph* g = new Graph();
	g->addVertex(n1);
	g->addVertex(n2);
	g->dijkstra(n1);
}


