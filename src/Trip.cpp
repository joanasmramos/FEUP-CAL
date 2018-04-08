#include <iostream>
#include <iomanip>
#include "Trip.h"

using namespace std;

Trip::Trip(int i, Vertex<int>* dp, Vertex<int>* dt) {
	carID = i;
	dep = dp;
	dest = dt;
}

Vertex<int>* Trip::getDep() {
	return dep;
}

Vertex<int>* Trip::getDest() {
	return dest;
}
