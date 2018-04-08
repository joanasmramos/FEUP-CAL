#include <iostream>
#include <vector>
#include "Vehicle.h"
#include "Graph.h"

class Management {
private:
	vector<Vehicle*> vehicles;
	Graph<int>* map; //read map text files
public:
	Management();
	bool read_nodes(string filename);
	bool read_edges(string filename); //TODO
	bool read_roads(string filename); //TODO
	void main_menu();
	void add_vehicle();
	void remove_vehicle();
	void add_trip();
	void remove_trip();
	void calc_itineraries() {}; //TODO
	int getInteger(string question, int min, int max);
	int find_vehicle(int id);
	//Node * find_node(unsigned long id);
};
