#include <iostream>
#include <iomanip>
#include <string>
#include "Graph.h"

using namespace std;

class Trip {
private:
	int carID;
	Node* dep;
	Node* dest;

public:
	/**
	 * @brief Trip constructor
	 * @param i Vehicle's ID
	 * @param dp Departure node
	 * @param dt Destiny node
	 */
	Trip(int i, Node* dp, Node* dt);
	/**
	 * @return Departure node
	 */
	Node* getDep();
	/**
	 * @return Destiny node
	 */
	Node* getDest();
	/**
	 * @return Vehicle's ID
	 */
	int getCarId();
	/**
	 * @brief Converts trip to string
	 * @return String trip
	 */
	string toString();
};
