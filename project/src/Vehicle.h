#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Graph.h"
#include "Trip.h"

using namespace std;

class Vehicle {

private:
	int id;
	float autonomy; //joules
	float consumptions; //relativo a outros
	float currentEnergy;
	vector< Trip* > trips;

public:
	/**
	 * @brief Vehicle constructor
	 * @param id ID
	 * @param aut autonomy
	 * @param cons consumptions
	 * @param ce current energy
	 */
	Vehicle(int id, float aut, float cons, float ce);
	/**
	 * @return id
	 */
	int getID();
	/**
	 * @brief Adds trip to vehicle
	 * @param t trip
	 */
	void addTrip(Trip* t);
	/**
	 * @brief Finds trip based on the departure and destiny
	 * @param dep Departure node
	 * @param dest Destiny node
	 * @return trip's index
	 */
	int findTrip(Node* dep, Node* dest);
	/**
	 * @brief Removes trip based on the departure and destiny
	 * @param dep Departure node
	 * @param dest Destiny node
	 * @return if it was removed
	 */
	bool removeTrip(Node* dep, Node* dest);
	/**
	 * @return trips
	 */
	vector< Trip* > getTrips();
	/**
	 * @return current energy
	 */
	float getCurrentEnergy();
	/**
	 * @return consumptions
	 */
	float getConsumptions();
	/**
	 * @brief Converts vehicle to string
	 * @return String vehicle
	 */
	string toString();
	/**
	 * @brief Set current energy to the maximum value (autonomy)
	 */
	void charge();
	/**
	 * @brief set current energy
	 * @param c current energy
	 */
	void setCurrentEnergy(float c);
};
