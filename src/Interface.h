#include <iostream>
#include <vector>
#include "Vehicle.h"

class Management {
private:
	vector<Vehicle*> vehicles;
	Graph* map; //read map text files
public:
	Management(); //to do
	bool read_nodes(string filename);
	void main_menu();
	void add_vehicle();
};
