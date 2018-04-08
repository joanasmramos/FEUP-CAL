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
	float aggravation; //o quanto mais gasta nas subidas //extra_consumption = aggravation * (inclination^2 / 2)
	float recovery; //o que recupera nas descidas //(joule/m)*%
	float currentEnergy;
	Vertex<int>* departure;
	Vertex<int>* destination;


public:
	Vehicle(float aut, float cons, float agg, float rec, float ce, Vertex<int>* dep, Vertex<int>* dest);
};
