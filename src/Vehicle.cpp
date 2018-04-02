#include "Vehicle.h"


Vehicle::Vehicle(int id, float aut, float cons, float agg, float rec, float ce, Node* dep, Node* dest) {
	this->id = id;
	autonomy = aut;
	consumptions = cons;
	aggravation = agg;
	recovery = rec;
	currentEnergy = ce;
	trips[0][0] = *dep;
	trips[0][1] = *dest;
};
