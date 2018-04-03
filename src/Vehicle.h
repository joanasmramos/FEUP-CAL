#include <iostream>
#include <iomanip>
#include <vector>
#include "Graph.h"
#include "Trip.h"

using namespace std;

class Vehicle {

private:
	int id;
	float autonomy;
	float consumptions;
	float aggravation; //o quanto mais gasta nas subidas
	float recovery; //o que recupera nas descidas
	float currentEnergy;
	vector< Trip* > trips;


public:
	Vehicle(int id, float aut, float cons, float agg, float rec, float ce);
	int getID();
	void addTrip(int i, Node* dest, Node* dep);
	int findTrip(Node* dep, Node* dest);
	bool removeTrip(Node* dep, Node* dest);
};
