#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Graph.h"
#include "Trip.h"

using namespace std;

class Vehicle {

private:
	int id;
	float autonomy; //joules
	float consumptions; //relativo a outros
	float currentEnergy;
	vector< Trip* > trips;


public:
	Vehicle(int id, float aut, float cons, float ce);
	int getID();
	void addTrip(int i, Node* dest, Node* dep);
	int findTrip(Node* dep, Node* dest);
	bool removeTrip(Node* dep, Node* dest);
	vector< Trip* > getTrips();
	float getCurrentEnergy();
	float getConsumptions();
	string toString();
};
