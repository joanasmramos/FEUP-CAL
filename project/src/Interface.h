#include <iostream>
#include <vector>
#include "Vehicle.h"
#include "graphviewer.h"

class Management {
private:
	vector<Vehicle*> vehicles;
	vector<Trip*> trips;
	Graph* map; //read map text files
public:
	/**
	 * @brief Management constructor. It creates de graph and calls the functions to read the information to the graph.
	 */
	Management();
	/**
	 * @brief Function to read nodes to a file.
	 * @param filename Name of the file
	 * @return true if it was read correctly, false otherwise
	 */
	bool read_nodes(string filename);
	/**
	 * @brief Function to read edges to a file.
	 * @param filename Name of the file
	 * @return true if it was read correctly, false otherwise
	 */
	bool read_edges(string filename);
	/**
	 * @brief Function to read roads to a file.
	 * @param filename Name of the file
	 * @return true if it was read correctly, false otherwise
	 */
	bool read_roads(string filename);
	/**
	 * @brief Function to read vehicles to a file.
	 * @param filename Name of the file
	 * @return true if it was read correctly, false otherwise
	 */
	bool read_vehicles(string filename);
	/**
	 * @brief Function to read trips to a file.
	 * @param filename Name of the file
	 * @return true if it was read correctly, false otherwise
	 */
	bool read_trips(string filename);
	/**
	 * @brief Creates the main menu.
	 */
	void main_menu();
	/**
	 * @brief Add vehicle according to the informations given by the user.
	 */
	void add_vehicle();
	/**
	 * @brief Remove vehicle according to the informations given by the user.
	 */
	void remove_vehicle();
	/**
	 * @brief Add trip according to the informations given by the user.
	 */
	void add_trip();
	/**
	 * @brief Remove trip according to the informations given by the user.
	 */
	void remove_trip();
	/**
	 * @brief This function the uses Dijkstra algorithm. It calculate all the trips made by each vehicle, updates the vehicle's current energy and prints all the paths.
	 */
	void calc_itineraries();
	/**
	 * @brief Auxiliar function to calc_itineraries()
	 * @param edges Vector containing a path of edges
	 * @return pseudo-distance combining the distance and the inclination of the path use to calculate the vehicle's consumption
	 */
	double getLength(vector<Edge*> edges);
	/**
	 * @brief controlled version to use std::cin mainly to get ID's
	 * @param question question printed
	 * @param min minimum number
	 * @param max maximum number
	 * @return string of the number
	 */
	string getInteger(string question, int min, int max);
	/**
	 * @brief Searches vehicle in the vehicles vector.
	 * @return Position in the vector
	 */
	int find_vehicle(int id);
	/**
	 * @brief Searches node in map
	 * @param id node's id
	 * @return node
	 */
	Node * find_node(string id);
	/**
	 * @brief Prints path by street. If it goes throw 2 or more edges on the same street only prints the street once.
	 * @param p Path of edges
	 */
	void print_path(vector<Edge*> p);
	/**
	 * @brief Creates a path made of edges from a path made of nodes
	 * @param path path made of nodes
	 * @return path made of edges
	 */
	vector<Edge *> getEdges(vector<string> path);
	/**
	 * @brief updates vehicles file
	 */
	void updateVehicles();
	/**
	 * @brief updates trips file
	 */
	void updateTrips();
	/**
	 * @brief prints vehicles file
	 */
	void print_vehicles();
	/**
	 * @brief prints trips file
	 */
	void print_trips();
	/**
	 * @brief exact search
	 */
	void exact_search();
	/**
	 * @brief approximate search
	 */
	void apro_search();
	/**
	 * @brief asks user to input the string he/she is looking for
	 */
	string getSearchString();
	/**
	 * @brief KMC matcher algorithm
	 */
	int KMPmatcher(string p, string t);
	/**
	 * @brief Compute-Prefix-Function
	 */
	void CPF(string p, int pi[]);

	/**
	* @brief computes the edit distance between a pattern and a text string
	* @param p pattern string
	* @param t text string
	* @return edit distance
	*/
	int editDistance(string p, string t);

	/**
	* @brief computes minimum of 3 values
	* @param a first value
	* @param b second value
	* @param c third value
	* @return minimum value
	*/
	int minimum(int a, int b, int c);

	Road* searchRoad(string name);
	
	void setup_GraphViewer();

	bool searchCross(vector<Road*> matched, vector<vector<Road*>> *cross);

	void manageCross(vector<Road*> matched);

	/**
		* @brief turns string to lower case string
		* @param s string to edit
		* @return string edited
		*/
	string strToLower(string s);
};
