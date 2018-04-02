#include <iostream>
#include <vector>
#include "Vehicle.h"

class Management {
private:
	vector<Vehicle*> vehicles;
	Graph* map; //read map text files
public:
	Management(){

		int inp=0;

		main_menu();

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

	}; //to do
	void main_menu();
	void add_vehicle();
};
