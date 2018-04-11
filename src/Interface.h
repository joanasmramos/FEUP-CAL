#include <iostream>
#include <vector>
#include "Vehicle.h"

class Management {
private:
	vector<Vehicle*> vehicles;
	vector<Trip*> trips;
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
	double getLength(vector<Edge*> edges);
	string getInteger(string question, int min, int max);
	int find_vehicle(int id);
	Node * find_node(string id);
	void print_path(vector<Edge*> p);
	vector<Edge *> getEdges(vector<string> path);
	void updateVehicles();
	void updateTrips();
	void print_vehicles();
	void print_trips();
};
