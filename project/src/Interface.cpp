#include <iostream>
#include <iomanip>
#include "Interface.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <math.h>
#include <cstdio>
#include "graphviewer.h"
#include <sstream>
#include <map>

using namespace std;

Management::Management(){

	map = new Graph();

	if (!((read_nodes("nodes_osm.txt") == true) &&
		(read_roads("streets_osm.txt") == true) &&
		(read_edges("edges_osm.txt") == true)))
		return;

	if (!(read_vehicles("Vehicles.txt") == true) && (read_trips("Trips.txt")))
			return;

//	if (!((read_nodes("Nodes.txt") == true) && (read_edges("Edges.txt") == true) && (read_roads("Streets.txt") == true)))
//		return;
//
//	if (!((read_vehicles("VehiclesTest.txt") == true) && (read_trips("TripsTest.txt"))))
//			return;

	map->setChargingPoints();
	map->organizeNodes();
	
	char answer;
	
	cout << "Would you like a visual representation of the map? (Y/N)\n";

	cin >> answer;

	while (cin.fail() || (answer != 'n' && answer != 'N' && answer != 'y' && answer != 'Y')) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Not an option, retrying\n";
		cout << "Would you like a visual representation of the map? (Y/N)\n";
		cin >> answer;
	}

	if (answer == 'y' || answer == 'Y')
		setup_GraphViewer();
	
	main_menu();
}

void Management::setup_GraphViewer() {
	GraphViewer *gv = new GraphViewer(1000, 600, false);

	gv->createWindow(1000, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(true);

	for (int i = 0; i < map->getNodes().size(); i++) {
		gv->addNode(map->getNodes()[i]->getId(), (long) map->getNodes()[i]->getLat() + 100, (long) map->getNodes()[i]->getLong()+ 100);
	}

	for (int i = 0; i < map->getEdges().size(); i++) {
		gv->addEdge(i, map->getEdges()[i]->getSourceId(), map->getEdges()[i]->getDestId(), EdgeType::UNDIRECTED);
	}
}

bool Management::read_nodes(string filename){

	ifstream instream;

	instream.open(filename);

	string info;
	string id;
	double latitude;
	double longitude;
	double altitude;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = info;
			getline(instream, info, ';');
			longitude = stod(info);
			getline(instream, info, ';');
			latitude = stod(info);
			getline(instream, info, '\n');
			altitude = stod(info);
			Node* newnode = new Node(id, latitude, longitude, altitude);

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
	string road_id, node1_id, node2_id;
	double distance, value;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			road_id = info;
			getline(instream, info, ';');
			node1_id = info;
			getline(instream, info, ';');
			node2_id = info;
			getline(instream, info, '\n');

			Node* node_1 = find_node(node1_id);
			Node* node_2 = find_node(node2_id);

			if (node_1 == NULL || node_2 == NULL) {
				cout << "Couldn't find node. Edge not created." << endl << node1_id << " " << node2_id << endl;
			} else {

				Edge * newedge = new Edge(road_id, node1_id, node2_id);

				distance = sqrt(pow(node_1->getLong()-(node_2->getLong()), 2) +
								  pow(node_1->getLat()-(node_2->getLat()), 2));

				value = distance * (1+((node_1->getAlt()-node_2->getAlt())/distance));

				newedge->setValue(value);

				node_1->addEdgeOut(newedge);
				node_2->addEdgeIn(newedge);

				this->map->addEdge(newedge);
			}
		}
	}
	else {
		cout << "Couldn't open edges file.\n";
		return false;
	}

	instream.close();
	return true;
}

bool stringToBool(string txt) {
	if (txt == "true" || txt == "True")
		return true;
	else
		return false;
}

bool Management::read_roads(string filename){

	ifstream instream(filename);

		string info;
		string road_id;
		string road_name;
		bool two_way;

		if(instream.is_open()) {
			while(!instream.eof()) {
				getline(instream, info, ';');
				road_id = info;
				getline(instream, info, ';');
				road_name = info;
				getline(instream, info, '\n');
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
		return true;
}

bool Management::read_vehicles(string filename) {

	ifstream instream(filename);

	string info;
	int id;
	float a, c, ce;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = stoi(info);
			getline(instream, info, ';');
			a = stof(info);
			getline(instream, info, ';');
			c = stof(info);
			getline(instream, info, ';');
			ce = stof(info);

			if (ce > a) {
				cout << "Invalid vehicle\n" << endl;
			} else {
				Vehicle* v = new Vehicle(id, a, c, ce);
				vehicles.push_back(v);
			}
		}
	}
	else {
		cout << "Couldn't open vehicles file.\n";
		return false;
	}

	instream.close();
	return true;
}

bool Management::read_trips(string filename) {

	ifstream instream(filename);

	string info;
	int id;
	string dep, dest;
	int index;

	if(instream.is_open()) {
		while(!instream.eof()) {
			getline(instream, info, ';');
			id = stoi(info);
			getline(instream, info, ';');
			dep = info;
			getline(instream, info, '\n');
			dest = info;

			index = find_vehicle(id);

			Node* node_1 = find_node(dep);
			Node* node_2 = find_node(dest);

			if (node_1 == NULL || node_2 == NULL) {
				cout << "Couldn't find node. Trip not created." << endl << dep << " " << dest << endl;
			} else if (index == -1) {
				cout << "Couldn't find vehicle. Trip not created." << endl;
			} else {
				Trip* t = new Trip(id, node_1, node_2);
				vehicles[index]->addTrip(t);
				trips.push_back(t);
			}
		}
	}
	else {
		cout << "Couldn't open trips file.\n";
		return false;
	}

	instream.close();
	return true;
}

void Management::main_menu() {
	cout << "Choose option: " << endl;
	cout << "1- Add vehicle" << endl;
	cout << "2- Remove vehicle" << endl;
	cout << "3- Add trip to vehicle" << endl;
	cout << "4- Remove trip from vehicle" << endl;
	cout << "5- Calculate and show best itineraries" << endl;
	cout << "6- Show vehicles" << endl;
	cout << "7- Show trips" << endl;
	cout << "8- Exact Search" << endl;
	cout << "9- Approximate Search" << endl;
	cout << "10- Exit" << endl;

	string option = getInteger("Option: ", 1, 10);

	switch (stoul(option)) {
		case 1:
			add_vehicle();
			updateVehicles();
			break;
		case 2:
			remove_vehicle();
			updateVehicles();
			updateTrips();
			break;
		case 3:
			add_trip();
			updateTrips();
			break;
		case 4:
			remove_trip();
			updateTrips();
			break;
		case 5:
			calc_itineraries();
			updateVehicles();
			break;
		case 6:
			print_vehicles();
			break;
		case 7:
			print_trips();
			break;
		case 8:
			exact_search();
			break;
		case 9:
			apro_search();
			break;
		case 10:
			cout << "Goodbye!\n";
			exit(0);

		default: 
			cout << "Not an option, retrying. \n";
			cin.clear();
			cin.ignore(10000, '\n');
			break;
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

	if (aut < ce) {
		cout << "The current energy needs to be smaller than the autonomy." << endl;
		return;
	}

	Vehicle* v_aux = new Vehicle(id, aut, cons, ce);
	vehicles.push_back(v_aux);

	cout << "Vehicle added successfully" << endl;
}

void Management::remove_vehicle() {
	int id = stoul(getInteger("Vehicle's ID: ", 0, 999999999));

	int index = find_vehicle(id);

	if (index == -1) {
		cout << "Vehicle not found" << endl;
		return;
	}

	vehicles.erase(vehicles.begin()+index);

	for(int i = 0; i < trips.size(); i++) {
		if (trips[i]->getCarId() == id) {
			trips.erase(trips.begin()+i);
			i--;
		}
	}

	cout << "Vehicle removed successfully" << endl;
}

void Management::add_trip() {

	int id = stoul(getInteger("Vehicle's ID: ", 0, 999999999));

	int i = find_vehicle(id);

	if (i == -1) {
		cout << "Vehicle not found" << endl;
		return;
	}

	string dep_id = getInteger("Departure point's ID: ", 0, 999999999);
	string dest_id = getInteger("Destiny point's ID: ", 0, 999999999);

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

	Trip* t = new Trip(id, dep, dest);
	vehicles[i]->addTrip(t);
	trips.push_back(t);

	cout << "Trip added successfully" << endl;

}

void Management::remove_trip() {

	int id = stoul(getInteger("Vehicle's ID: ", 0, 999999999));

	int i = find_vehicle(id);

	if (i == -1) {
		cout << "Vehicle not found" << endl;
		return;
	}

	string dep_id;
	string dest_id;
	cout << "Departure point's ID: ";
	cin >> dep_id;
	cout << "Destiny point's ID: ";
	cin >> dest_id;

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

	if (vehicles[i]->removeTrip(dep, dest)) {
		cout << "Trip removed successfully" << endl;
		for (int i= 0; i < trips.size(); i++) {
			if (trips[i]->getDest()->getId() == dest_id && trips[i]->getDep()->getId() == dep_id && trips[i]->getCarId() == id) {
				trips.erase(trips.begin()+i);
				break;
			}
		}
	}
	else
		cout << "Trip not found" << endl;
}

void Management::calc_itineraries() {

	double length = 0;
	vector<string> path, dep_to_cp, cp_to_dest;
	vector<vector<string>> chargingPointsPaths;
	vector<double> chargingPointsDistance;
	int min_index;
	double min;
	vector<Edge*> path_edges;

	for (int i = 0; i < vehicles.size(); i++) {

		cout << i+1 << "º Vehicle:" << endl << endl;

		length = 0;

		for (int j = 0; j < vehicles[i]->getTrips().size(); j++) {

			cout << j+1 << "º Trip:" << endl << endl;

			path = map->getShortestPath(vehicles[i]->getTrips()[j]->getDep()->getId(), vehicles[i]->getTrips()[j]->getDest()->getId());

			path_edges = getEdges(path);

			length = vehicles[i]->getConsumptions() * getLength(path_edges);

			if(length > ((double) vehicles[i]->getCurrentEnergy())) {

				for (int k = 0; k < map->getChargingPoints().size(); k++) {

					dep_to_cp = map->getShortestPath(vehicles[i]->getTrips()[j]->getDep()->getId(), map->getChargingPoints()[k]->getId());

					chargingPointsPaths.push_back(dep_to_cp);
					chargingPointsDistance.push_back(getLength(getEdges(dep_to_cp)));

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

					cp_to_dest.erase(cp_to_dest.begin());

					path = dep_to_cp;

					path.insert(path.end(), cp_to_dest.begin(), cp_to_dest.end());

					path_edges = getEdges(path);

					length = getLength(path_edges);

					vehicles[i]->charge();
					vehicles[i]->setCurrentEnergy(vehicles[i]->getCurrentEnergy() - (length - min));

					cout << "You need to stop for charging." << endl;
				}
			} else {
				vehicles[i]->setCurrentEnergy(vehicles[i]->getCurrentEnergy() - length);
			}

			cout << "Path: " << endl;
			print_path(path_edges);
			cout << "Energy spent: " << endl;
			cout << length << endl;
		}
	}

	updateVehicles();

}

void Management::print_path(vector<Edge*> p) {
	string last_printed;
	string currentName;

	for (int i = 0; i < p.size(); i++) {
		currentName = map->findRoad(p[i]->getRoadId())->getName();
		if(last_printed != currentName) {
			cout << currentName;
			if (i != p.size()-1)
				cout << " - ";
		}
		if (i == p.size()-1)
			cout << endl;

		last_printed = currentName;
	}
}

vector<Edge*> Management::getEdges(vector<string> path) {

	vector<Edge*> v;

	for (int i = 0; i < path.size()-1; i++) {
		Edge* e = map->findEdge(find_node(path[i])->getId(), find_node(path[i+1])->getId());
		v.push_back(e);
	}

	return v;
}

double Management::getLength(vector<Edge*> edges) {

	double length = 0;

	for (int i = 0; i < edges.size(); i++) {
		length += edges[i]->getValue();
	}

	return length;
}

string Management::getInteger(string question, int min, int max) {
	//local variables
	bool error = false;
	string option;

	do
	{
		option = "";
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

	} while (!(stoul(option) >= min && stoul(option) <= max));

	cin.ignore(1000, '\n');
	return option;
}

Node * Management::find_node(string id) {
	return map->findNode(id);
}

void Management::updateVehicles() {

	ofstream outstream;

	outstream.open("VehiclesTest.txt");

	if(outstream.is_open()) {
		for (int i = 0; i < vehicles.size(); i++) {
			outstream << vehicles[i]->toString();
			if (i != vehicles.size()-1)
				outstream << "\n";
		}
	} else {
		cout << "Couldn't open nodes file.\n";
	}
	outstream.close();
}

void Management::updateTrips() {

	ofstream outstream;

	outstream.open("TripsTest.txt");

	if(outstream.is_open()) {
		for (int i = 0; i < trips.size(); i++) {
			outstream << trips[i]->toString();
			if (i != trips.size()-1)
				outstream << "\n";
		}
	} else {
		cout << "Couldn't open nodes file.\n";
	}
	outstream.close();
}

void Management::print_vehicles() {
	cout << endl;
	for (int i = 0; i < vehicles.size(); i++) {
		cout << vehicles[i]->toString();
		if (i != vehicles.size()-1)
			cout << "\n";
	}
	cout << endl;
	cout << endl;
}

void Management::print_trips() {
	cout << endl;
	for (int i = 0; i < trips.size(); i++) {
		cout << trips[i]->toString();
		if (i != trips.size()-1)
			cout << "\n";
	}
	cout << endl;
	cout << endl;
}

bool Management::searchCross(vector<Road*> matched, vector<vector<Road*>> *cross) {

	vector<Road*> empty;

	Node* aux = nullptr;
	bool hit = false;

	for (int i = 0; i < matched.size(); i++) {

		cross->push_back(empty);

		for (int j = 0; j < matched[i]->getNodesRoad().size(); j++) {

			if (matched[i]->getNodesRoad()[j]->getChargingPoint() == true) {
				for (int k = 0; k < map->getRoads().size(); k++) {
					if (map->getRoads()[k]->getId() != matched[i]->getId()) {
						for(int l = 0; l < map->getRoads()[k]->getNodesRoad().size(); l++) {
							if (matched[i]->getNodesRoad()[j] == map->getRoads()[k]->getNodesRoad()[l]
								&& map->getRoads()[k]->getNodesRoad()[l] != aux) {
								aux = matched[i]->getNodesRoad()[j];
								(*cross)[i].push_back(map->getRoads()[k]);
								hit = true;
							}
						}
					}
				}
			}
		}
	}

	return hit;

}

void Management::manageCross(vector<Road*> matched) {

	cout << endl << "We found the following streets matching your search input:" << endl;

	for (int i = 0; i < matched.size(); i++) {
		cout << matched[i]->getName() << endl;
	}

	cout << endl;

	vector<vector<Road*>> cross;

	searchCross(matched, &cross);

	bool crossFound = false;

	if(matched.size() > 0){

		for(int i = 0; i < matched.size(); i++) {


			if (cross.size() != 0) {
				if (cross[i].size() != 0) {

					if (!crossFound) {
						cout << "We found charging point at: \n";
						crossFound = true;
					}

					for (int j = 0; j < cross[i].size(); j++) {

						cout << matched[i]->getName() << " - " << cross[i][j]->getName() << endl;
					}
				}
			}

		}

		if (!crossFound) {
			cout << "We couldn't charging point in that street. \n";
		}
	}

	else{
		cout << "Sorry, cant find that place...\n";
	}

	cout << endl;
}

void Management::exact_search() {
	cout << endl;

	string p;
	vector<Road*> roads, matched, empty;

	int res;
	unsigned int i;

	p = getSearchString();
	roads = this->map->getRoads();

	for(i = 0; i < roads.size(); i++){
		res = KMPmatcher(p, strToLower(roads[i]->getName()));
		if(res > 0){
			matched.push_back(roads[i]);
		}
	}

	manageCross(matched);

}

int Management::minimum(int a, int b, int c) {
	if (a <= b && b <= c) {
		return a;
	}
	else if (b <= a && b <= c) {
		return b;
	}
	else return c;
}

int Management::editDistance(string p, string t) {
	if (t == "")
		return p.length();

	vector<vector<int>> D(p.length(), vector<int>(t.length()));

	for (int i = 0; i < p.length(); i++) {
		D[i][0] = i;
	}

	for (int j = 0; j < t.length(); j++) {
		D[0][j] = j;
	}

	for (int i = 1; i < p.length(); i++) {
		for (int j = 1; j < t.length(); j++) {
			if (tolower(p[i]) == tolower(t[j])) {
				D[i][j] = D[i - 1][j - 1];
			}
			else {
				D[i][j] = 1 + minimum(D[i - 1][j - 1], D[i - 1][j], D[i][j - 1]);
			}
		}
	}

	if (t.length() > p.length()) {
		if (D[p.length() - 1][p.length() - 1] == 0) {
			return 0;
		}
	}

	return D[p.length() - 1][t.length() - 1];
}

void Management::apro_search() {
	cout << endl;

	string p;
	vector<Road*> roads;

	p = getSearchString();

	roads = this->map->getRoads();

	multimap<int, string> distances;

	for (auto it = roads.begin(); it != roads.end(); it++) {
		distances.insert(pair<int, string> (editDistance(p, (*it)->getName()), (*it)->getName()));
	}

	cout << "\nWe found... \n";

	int i = 0;
	for (auto it = distances.begin(); it != distances.end(); it++) {
		if (i > 5) // mostra 5 melhores opções
			break;
		cout << left << setw(35) << (*it).second << (*it).first << endl;
		i++;
	}

	cout << endl;

	vector<Road*> r;


	for (auto it = distances.begin(); it != distances.end(); it++) {
		r.push_back(searchRoad((*it).second));
	}

	for (int i = 0; i < r.size(); i++) {
		vector<Road*> aux;
		vector<vector<Road*>> cross;
		aux.push_back(r[i]);

		if (searchCross(aux, &cross)) {

			cout << "Did you mean " << r[i]->getName() << "?\nWe found a charging point there:\n";

			for (int j = 0; j < cross[0].size(); j++) {
				cout << aux[0]->getName() << " - " << cross[0][j]->getName() << endl;
			}
			break;
		}
	}

	cout << endl;

}

string Management::getSearchString(){
	string s;

	cout << "What are you looking for?" << endl;
	getline(cin, s);

	return s;
}

Road* Management::searchRoad(string name) {
	for (int i = 0; i < map->getRoads().size(); i++) {
		if (map->getRoads()[i]->getName() == name)
			return map->getRoads()[i];
	}

	return nullptr;
}

int Management::KMPmatcher(string pattern, string text){
		int * pi = new int[pattern.length()];
		int nOccurrences = 0;
		CPF(pattern, pi);

		int n = text.length(), m = pattern.length();
		int q = 0, i = 0;

		while( i < n){
			if (pattern[q] == text[i]){
				q++;
				i++;
			}
			if (q == m){
				q = pi[q-1];
				nOccurrences++;
			}
			else if (i < n && pattern[q] != text[i]){
				if (q != 0)
					q= pi[q-1];
				else i++;
			}

		}

		delete [] pi;
		return nOccurrences;
}

void Management::CPF(string pattern, int pi[]){
	int m = pattern.length(), k = 0;
		pi[0] = 0;
		for (int q = 1; q < m; q++) {
			if (pattern[q] == pattern[k]) {
				k++;
				pi[q] = k;
			} else {
				if (k != 0)
					k = pi[k - 1];
				else
					pi[q] = 0;
			}

		}
}

string Management::strToLower(string s){
	string s2;
	int i;
	char c;

	for(i = 0; i < s.length(); i++){
			 c= tolower(s[i]);
			 s2.push_back(c);

		}
	return s2;
}


