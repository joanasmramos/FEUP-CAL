#include <iostream>
#include <iomanip>
#include "Trip.h"

using namespace std;

Trip::Trip(int i, Node* dp, Node* dt) {
	carID = i;
	dep = dp;
	dest = dt;
}

Node* Trip::getDep() {
	return dep;
}

Node* Trip::getDest() {
	return dest;
}
