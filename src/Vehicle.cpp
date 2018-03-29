#include "Vehicle.h"

Vehicle::Vehicle(float aut, float cons, float agg, float rec, float ce, Node dep, Node dest) {
	autonomy = aut;
	consumptions = cons;
	aggravation = agg;
	recovery = rec;
	currentEnergy = ce;
};
