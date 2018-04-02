#include <iostream>
#include "Interface.h"
#include "Graph.h"

using namespace std;


void Management::main_menu() {
	cout << "Choose option: " << endl;
	cout << "1- Add vehicle" << endl;
	cout << "2- Remove vehicle" << endl;
	cout << "3- Show vehicle's best itinerary" << endl;
	cout << "4- Exit" << endl;
}

void Management::add_vehicle() {

	float aut, cons, agg, rec, ce;
	int dest_id, dep_id, id;

	cout << "ID: ";
	cin >> id;
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

	Node* dep = map->findNode(dep_id);

	cout << "Destination: ";
	cin >> dest_id;

	Node* dest = map->findNode(dest_id);

	Vehicle* v_aux = new Vehicle(id, aut, cons, agg, rec, ce, dep, dest);
	vehicles.push_back(v_aux);
}

Management::Management(){

	int inp=0;

	main_menu();

	while(inp != 4){
		cin >> inp;

		switch(inp){
		case 1:
			add_vehicle();
			break;
		case 2:

			break;
		case 3:

			break;

		}
	}

}
