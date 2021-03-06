#include "Vehicle.h"


Vehicle::Vehicle(int id, float aut, float cons, float ce) {
	this->id = id;
	autonomy = aut;
	consumptions = cons;
	currentEnergy = ce;
};

int Vehicle::getID() {
	return id;
}

float Vehicle::getCurrentEnergy() {
	return currentEnergy;
}

float Vehicle::getConsumptions() {
	return consumptions;
}

void Vehicle::addTrip(Trip* t) {
	trips.push_back(t);
}

int Vehicle::findTrip(Node* dep, Node* dest) {

	for (int i = 0; i < trips.size(); i++) {
		if (dep == trips[i]->getDep() && dest == trips[i]->getDest()) {
			return i;
		}
	}
	return -1;
}

bool Vehicle::removeTrip(Node* dep, Node* dest) {

	int i = findTrip(dep, dest);

	if (i == -1) {
		return false;
	} else {
		trips.erase(trips.begin()+i);
		return true;
	}
}

vector< Trip* > Vehicle::getTrips() {
	return trips;
}

string Vehicle::toString() {

	string vehicle = "";

	vehicle = to_string(id) + "; " + to_string(autonomy) + "; " + to_string(consumptions) + "; " + to_string(currentEnergy);

	return vehicle;
}

void Vehicle::charge() {
	currentEnergy = autonomy;
}

void Vehicle::setCurrentEnergy(float c) {
	currentEnergy = c;
}
