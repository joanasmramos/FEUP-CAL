#include <iostream>
#include "Interface.h"


using namespace std;

Management::Management(){

	if (!(read_nodes("A.txt") == true) &&
		(read_roads("B.txt") == true) &&
		(read_edges("C.txt") == true))
		return;


	main_menu();
}

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
			Node* newnode = new Node(id, latitude, longitude);
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

bool Management::read_edges(string filename){
	ifstream instream(filename);

	string info;
	unsigned long road_id, node1_id, node2_id;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			road_id = stoi(info);
			getline(instream, info, ';');
			node1_id = stoi(info);
			getline(instream, info, ';');
			node2_id = stoi(info);

			if(find_node(node1_id) == NULL || find_node(node2_id) == NULL)
				break;

			Edge * newedge = new Edge(road_id, node1_id, node2_id);
			find_node(node1_id)->addEdgeOut(newedge);
			find_node(node2_id)->addEdgeIn(newedge);

			this->map->addEdge(newedge);
		}
	}
	else {
		cout << "Couldn't open file.\n";
		return false;
	}

	instream.close();
	return false;
}

bool stringToBool(string txt) {
	if (txt == "true")
		return true;
	else
		return false;
}

bool Management::read_roads(string filename){
	ifstream instream(filename);

		string info;
		unsigned long road_id;
		string road_name;
		bool two_way;

		if(instream.is_open()) {
			while(!instream.eof()) {
				getline(instream, info, ';');
				road_id = stoi(info);
				getline(instream, info, ';');
				road_name = info;
				getline(instream, info, ';');
				two_way = stringToBool(info);

				Road* newroad = new Road(road_id, road_name, two_way);
				this->map->addRoad(newroad);

			}
		}
		else {
			cout << "Couldn't open file.\n";
			return false;
		}

		instream.close();
		return false;
}

void Management::main_menu() {
	cout << "Choose option: " << endl;
	cout << "1- Add vehicle" << endl;
	cout << "2- Remove vehicle" << endl;
	cout << "3- Add trip to car" << endl;
	cout << "4- Remove trip from car" << endl;
	cout << "5- Show best itineraries" << endl;
	cout << "6- Exit" << endl;

	int option = getInteger("Option: ", 1, 6);

	switch (option) {
		case 1:
			add_vehicle();
			break;
		case 2:
			remove_vehicle(); //TODO
			break;
		case 3:
			add_trip(); //TODO
			break;
		case 4:
			remove_trip(); //TODO
			break;
		case 5:
			calc_itineraries(); //TODO
			break;

		default: break;
	}
}

int Management::find_vehicle(int id) {
	for (int i = 0; i < vehicles.size(); i++) {
		if (id == vehicles[i]->getID()) {
			return i;
		}
	}
	return -1;
}

void Management::add_vehicle() {

	float aut, cons, agg, rec, ce;
	int dest_id, dep_id, id;
	Node* dep = NULL, *dest = NULL;

	cout << "ID: " << endl;
	cin >> id;
	cout << "Autonomy: " << endl;
	cin >> aut;
	cout << "Consumption: ";
	cin >> cons;
	cout << "Ascendance aggravation (percentage/degree): " << endl;
	cin >> agg;
	cout << "Regenerative braking (percentage/degree): " << endl;
	cin >> rec;
	cout << "Current deposit (m): " << endl;
	cin >> ce;
//	while(dep == NULL){
//		cout << "Departure: ";
//		cin >> dep_id;
//
//		dep = map->findNode(dep_id);
//		if(dep == NULL)
//			cout << "Departure not valid\n";
//	}
//
//	while(dest==NULL){
//		cout << "Destination: ";
//		cin >> dest_id;
//
//		dest = map->findNode(dest_id);
//		if(dest == NULL)
//				cout << "Destination not valid\n";
//	}

	Vertex<int>* dep = map->findVertex(dep_id);
	Vertex<int>* dest = map->findVertex(dest_id);

	Vehicle* v_aux = new Vehicle(id, aut, cons, agg, rec, ce);
	vehicles.push_back(v_aux);

	cout << "Vehicle added successfully" << endl;
}

void Management::remove_vehicle() {
	int id = getInteger("Vehicle's ID: ", 0, 999999999);

	int i = find_vehicle(id);

	if (i == -1) {
		cout << "Vehicle not found" << endl;
		return;
	}

	vehicles.erase(vehicles.begin()+i);

	cout << "Vehicle removed successfully" << endl;

}

void Management::add_trip() {

	int id = getInteger("Vehicle's ID: ", 0, 999999999);

	int i = find_vehicle(id);

	if (i == -1) {
		cout << "Vehicle not found" << endl;
		return;
	}

	int dep_id = getInteger("Departure point's ID: ", 0, 999999999);
	int dest_id = getInteger("Destiny point's ID: ", 0, 999999999);

	auto dep = map->findNode(dep_id);
	if (dep == NULL) {
		cout << "Point not found" << endl;
		return;
	}
	auto dest = map->findNode(dest_id);
	if (dep == NULL) {
		cout << "Point not found" << endl;
		return;
	}

	vehicles[i]->addTrip(id, dep, dest);

	cout << "Trip added successfully" << endl;

}

void Management::remove_trip() {

	int id = getInteger("Vehicle's ID: ", 0, 999999999);

	int i = find_vehicle(id);

	if (i == -1) {
		cout << "Vehicle not found" << endl;
		return;
	}

	int dep_id = getInteger("Departure point's ID: ", 0, 999999999);
	int dest_id = getInteger("Destiny point's ID: ", 0, 999999999);

	auto dep = map->findNode(dep_id);
	if (dep == NULL) {
		cout << "Point not found" << endl;
		return;
	}
	auto dest = map->findNode(dest_id);
	if (dep == NULL) {
		cout << "Point not found" << endl;
		return;
	}

	if (vehicles[i]->removeTrip(dep, dest))
		cout << "Trip removed successfully" << endl;
	else
		cout << "Trip not found" << endl;
}

int Management::getInteger(string question, int min, int max) {
	//local variables
	bool error = false;
	int option;

	do
	{
		option = 0;
		do
		{
			cout << question;
			if (error == true)
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin >> option;
			error = true;

		} while (cin.fail());
		error = false;

	} while (!(option >= min && option <= max));

	cin.ignore(1000, '\n');
	return option;
}

Node * Management::find_node(unsigned long id) {
	return map->findNode(id);
}
