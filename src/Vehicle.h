#include <iostream>
#include <iomanip>
#include "Graph.h"
#include <vector>

using namespace std;

class Vehicle {

private:
	int id;
	float autonomy;
	float consumptions;
	float aggravation; //o quanto mais gasta nas subidas
	float recovery; //o que recupera nas descidas
	float currentEnergy;
	vector<vector<Node>> trips;


public:
	Vehicle(int id, float aut, float cons, float agg, float rec, float ce, Node* dep, Node* dest);
};
