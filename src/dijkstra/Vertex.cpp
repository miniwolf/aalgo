#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(int id):id_(id){}

void Vertex::addNeighbour(Vertex* vertex, int d){
	Edge* e = new Edge(vertex,d);	
	edges_.push_back(e);
	cout << "Vector knows " << int(edges_.size()) << " vertices \n" << endl;		
}
