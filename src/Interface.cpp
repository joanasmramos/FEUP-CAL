#include <iostream>
#include "Interface.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

Management::Management(){
	map = new Graph();

	if (!((read_nodes("A.txt") == true) &&
		(read_roads("B.txt") == true) &&
		(read_edges("C.txt") == true)))
		return;

	if (!(read_vehicles("Vehicles.txt") == true) && (read_trips("Trips.txt")))
			return;

	main_menu();
}

bool Management::read_nodes(string filename){

	ifstream instream;

	instream.open(filename, ios::in);

	string info;
	unsigned long id;
	double latitude;
	double longitude;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = stoul(info);
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
		cout << "Couldn't open nodes file.\n";
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
			road_id = stoul(info);
			getline(instream, info, ';');
			node1_id = stoul(info);
			getline(instream, info, ';');
			node2_id = stoul(info);

			if(find_node(node1_id) == NULL || find_node(node2_id) == NULL)
				break;

			Edge * newedge = new Edge(road_id, node1_id, node2_id);

			double distance = sqrt(pow(find_node(node1_id)->getLong()-(find_node(node2_id)->getLong()), 2) +
							  pow(find_node(node1_id)->getLat()-(find_node(node2_id)->getLat()), 2))*1000;

			double value = distance * (1+((find_node(node1_id)->getAlt()-find_node(node2_id)->getAlt())/distance));

			newedge->setValue(value);

			find_node(node1_id)->addEdgeOut(newedge);
			find_node(node2_id)->addEdgeIn(newedge);

			this->map->addEdge(newedge);
		}
	}
	else {
		cout << "Couldn't open edges file.\n";
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
				road_id = stoul(info);
				getline(instream, info, ';');
				road_name = info;
				getline(instream, info, ';');
				two_way = stringToBool(info);

				Road* newroad = new Road(road_id, road_name, two_way);
				this->map->addRoad(newroad);

			}
		}
		else {
			cout << "Couldn't open roads file.\n";
			return false;
		}

		instream.close();
		return false;
}

bool Management::read_vehicles(string filename) {

	//////////////////////////////////////////////////
	//////////////Falta altitude//////////////////////
	//////////////////////////////////////////////////

	ifstream instream(filename);

	string info;
	int id;
	float a, c, ce;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = stoi(info);
			getline(instream, info, ';');
			a = stoi(info);
			getline(instream, info, ';');
			c = stoi(info);
			getline(instream, info, ';');
			ce = stoi(info);

			Vehicle* v = new Vehicle(id, a, c, ce);
			vehicles.push_back(v);
		}
	}
	else {
		cout << "Couldn't open vehicles file.\n";
		return false;
	}

	instream.close();
	return false;
}

bool Management::read_trips(string filename) {
	ifstream instream(filename);

	string info;
	int id, dep, dest;
	int index;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = stoi(info);
			getline(instream, info, ';');
			dep = stoi(info);
			getline(instream, info, ';');
			dest = stoi(info);

			index = find_vehicle(id);

			vehicles[index]->addTrip(id, map->findNode(dep), map->findNode(dest));
		}
	}
	else {
		cout << "Couldn't open trips file.\n";
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
			remove_vehicle();
			break;
		case 3:
			add_trip();
			break;
		case 4:
			remove_trip();
			break;
		case 5:
			calc_itineraries(); //TODO
			break;
		case 6:
			return;

		default: break;
	}

	main_menu();
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

	float aut, cons, ce;
	int id;

	cout << "ID: " << endl;
	cin >> id;
	cout << "Autonomy: " << endl;
	cin >> aut;
	cout << "Consumption: " << endl;
	cin >> cons;
	cout << "Current deposit (m): " << endl;
	cin >> ce;

	Vehicle* v_aux = new Vehicle(id, aut, cons, ce);
	vehicles.push_back(v_aux);

	cout << "Vehicle added successfully" << endl;

	main_menu();
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

	main_menu();

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

void Management::calc_itineraries() {

	//É preciso calcular a "distancia" (ja contabiliza subidas e descidas) entre dois pontos, se for maior que a autonomia temos de calcular a distancia
	//ao chargingPoint mais proximo e dai para o node final.
	//A distancia depois multiplica-se pelos consumos do carro, assim há alguma personalização de cada carro. Isto é, se a "distancia" for 100,
	//a energia atual for 90 e os consumos desse carro forem 0.8 o carro faz o caminho e ainda fica com 10 de energia

	//Sempre que se calcula um caminho imprimi-se o vetor dos pontos que depois devia ser convertido para as ruas

//	cout << vehicles[0]->getTrips()[0]->getDep()->getId() << endl;
//	cout << vehicles[0]->getTrips()[0]->getDest()->getId() << endl;


	double length = 0;
	vector<unsigned long> path, dep_to_cp, cp_to_dest;
	vector<vector<unsigned long>> chargingPointsPaths;
	vector<double> chargingPointsDistance;
	int min_index;
	double min;

	for (int i = 0; i < vehicles.size(); i++) {

		length = 0;

		for (int j = 0; j < vehicles[i]->getTrips().size(); j++) {

			path = map->getShortestPath(vehicles[i]->getTrips()[j]->getDep()->getId(), vehicles[i]->getTrips()[j]->getDest()->getId());

			length = vehicles[i]->getConsumptions() * getLength(path);

			if(length > ((double) vehicles[i]->getCurrentEnergy())) {
				for (int k = 0; k < map->getChargingPoints().size(); k++) {

					dep_to_cp = map->getShortestPath(vehicles[i]->getTrips()[j]->getDep()->getId(), map->getChargingPoints()[k]->getId());

					chargingPointsPaths.push_back(dep_to_cp);
					chargingPointsDistance.push_back(getLength(path));
				}

				min_index = 0;
				min = vehicles[i]->getConsumptions() * chargingPointsDistance[0];

				for (int k = 1; k < chargingPointsDistance.size(); k++) {
					if(chargingPointsDistance[k] < min) {
						min_index = k;
						min = vehicles[i]->getConsumptions() * chargingPointsDistance[k];
					}
				}

				if (min > (double) vehicles[i]->getCurrentEnergy()) {
					cout << "You don't have enough energy to get to either your destine nor the nearest charging point." << endl;
				} else {
					dep_to_cp = chargingPointsPaths[min_index];
					cp_to_dest = map->getShortestPath(map->getChargingPoints()[min_index]->getId(), vehicles[i]->getTrips()[j]->getDest()->getId());

					path = dep_to_cp;

					path.insert(path.end(), cp_to_dest.begin(), cp_to_dest.end());

					cout << "You need to stop for charging." << endl;
				}
			}
			cout << path.size() << endl;
			cout << length << endl;
		}
	}
}


double Management::getLength(vector<unsigned long> path) {

	double length = 0;

	for (int i = 0; i < path.size()-1; i++) {
		length += map->findEdge(map->findNode(path[i])->getId(), map->findNode(path[i+1])->getId())->getValue();
	}

	return length;
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
