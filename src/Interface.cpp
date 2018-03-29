#include <iostream>
#include "Interface.h"

using namespace std;


void Management::main_menu() {
	cout << "Choose option: " << endl;
	cout << "1- Add vehicle" << endl;
	cout << "2- Remove vehicle" << endl;
	cout << "1- Show vehicle's best itinerary" << endl;
}

void Management::add_vehicle() {
	float aut, cons, agg, rec, ce;
	int dest_id, dep_id;

	cout << "Autonomy: ";
	cin >> aut;
	cout << "Consumption: ";
	cin >> cons;
	cout << "Ascendance aggravation (percentage/degree): ";
	cin >> agg;
	cout << "Regenerative braking (percentage/degree): ";
	cin >> rec;
	cout << "Current deposit (m): ";
	cin >> ce;
	cout << "Departure: ";
	cin >> dep_id;
	cout << "Destination: ";
	cin >> dest_id;


}
