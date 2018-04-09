#include <iostream>
#include <iomanip>
#include <string>
#include "Graph.h"

using namespace std;

class Trip {
private:
	int carID;
	Node* dep;
	Node* dest;

public:
	Trip(int i, Node* dp, Node* dt);
	Node* getDep();
	Node* getDest();
	string toString();
};
