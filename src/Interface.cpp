#include <iostream>
#include "Interface.h"
#include "Graph.h"
#include <fstream>
#include <string>

using namespace std;

bool Management::read_nodes(string filename){
	ifstream instream(filename);

	string info;
	unsigned long id;
	double latitude;
	double longitude;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = stoi(info);
			getline(instream, info, ';');
			getline(instream, info, ';');
			getline(instream, info, ';');
			longitude = stod(info);
			getline(instream, info, '\n');
			latitude = stod(info);
			Node newnode = new Node(id, latitude, longitude);
			this->map->addNode(newnode);
		}
	}
	else {
		cout << "Couldn't open file.\n";
		return false;
	}

	instream.close();
	return true;
}

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
	Node* dep = NULL, *dest = NULL;

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
	while(dep == NULL){
		cout << "Departure: ";
		cin >> dep_id;

		dep = map->findNode(dep_id);
		if(dep == NULL)
			cout << "Departure not valid\n";
	}

	while(dest==NULL){
		cout << "Destination: ";
		cin >> dest_id;

		dest = map->findNode(dest_id);
		if(dest == NULL)
				cout << "Destination not valid\n";
	}


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
