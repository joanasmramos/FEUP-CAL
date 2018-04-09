#include <iostream>
#include <iomanip>
#include <vector>
#include "Graph.h"
#include "Trip.h"

using namespace std;

class Vehicle {

private:
	int id;
	float autonomy; //joules
	float consumptions; //joules/metro
//	float aggravation; //o quanto mais gasta nas subidas //extra_consumption = aggravation * (inclination^2 / 2)
//	float recovery; //o que recupera nas descidas //(joule/m)*%
	float currentEnergy;
	vector< Trip* > trips;


public:
	Vehicle(int id, float aut, float cons, float ce);
	int getID();
	void addTrip(int i, Node* dest, Node* dep);
	int findTrip(Node* dep, Node* dest);
	bool removeTrip(Node* dep, Node* dest);
};
