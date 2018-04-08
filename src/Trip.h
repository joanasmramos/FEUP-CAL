#include <iostream>
#include <iomanip>
#include "Graph.h"

using namespace std;

class Trip {
private:
	int carID;
	Vertex<int>* dep;
	Vertex<int>* dest;

public:
	Trip(int i, Vertex<int>* dp, Vertex<int>* dt);
	Vertex<int>* getDep();
	Vertex<int>* getDest();
};
