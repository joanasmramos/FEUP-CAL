#include <iostream>
#include <iomanip>
#include "Graph.h"

using namespace std;

class Vehicle {

private:
	float autonomy;
	float consumptions;
	float aggravation; //o quanto mais gasta nas subidas
	float recovery; //o que recupera nas descidas
	float currentEnergy;
	Node* departure;
	Node* destination;


public:
	Vehicle(float aut, float cons, float agg, float rec, float ce, Node* dep, Node* dest);
};
