#include <iostream>
#include <vector>
#include "Vehicle.h"

class Management {
private:
	vector<Vehicle*> vehicles;
	Graph* map; //read map text files
public:
	Management();
	bool read_nodes(string filename);
	bool read_edges(string filename);
	bool read_roads(string filename);
	bool read_vehicles(string filename);
	bool read_trips(string filename);
	void main_menu();
	void add_vehicle();
	void remove_vehicle();
	void add_trip();
	void remove_trip();
	void calc_itineraries(); //TODO
	double getLength(vector<string> path);
	string getInteger(string question, int min, int max);
	int find_vehicle(int id);
	Node * find_node(string id);
};
