#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

using namespace std;

class Node;
class Edge;
class Road;
class Graph;

#define INF numeric_limits<double>::max()

class Edge {
private:
	string roadID;
	string destID; //next unique edge ID.
	string sourceID; // unique id of the edge.
	double value; //size of the edge

public:
	friend class Graph;
	/**
	 * @brief Edge constructor
	 * @param roadid Road ID
	 * @param idsource Source ID
	 * @param iddest Destiny ID
	 */
	Edge(string roadid, string idsource, string iddest) {
		roadID = roadid;
		sourceID = idsource;
		destID = iddest;
		value = INF;
	}

	/**
	 * @return destID
	 */
	string getDestId() const {
		return destID;
	}

	/**
	 * @brief sets destiny ID
	 * @param destId Destiny ID
	 */
	void setDestId(string destId) {
		destID = destId;
	}

	/**
	 * @return RoadID
	 */
	string getRoadId() const {
		return roadID;
	}

	/**
	 * @brief sets road ID
	 * @param roadId Road ID
	 */
	void setRoadId(string roadId) {
		roadID = roadId;
	}

	/**
	 * @return sourceID
	 */
	string getSourceId() const {
		return sourceID;
	}

	/**
	 * @brief sets source ID
	 * @param sourceId source ID
	 */
	void setSourceId(string sourceId) {
		sourceID = sourceId;
	}

	/**
	 * @return value
	 */
	double getValue() {
		return value;
	}

	/**
	 * @brief sets value
	 * @param v value
	 */
	void setValue(double v) {
		value = v;
	}

	/**
	 * @brief Equals operator
	 * @param e1 second edge
	 * @return if they are the same
	 */
	bool operator==(const Edge e1){
		return (e1.roadID == this->roadID);
	}
};

class Node {

private:
	string id; ///< Node ID
	//É preciso as coordenadas dos pontos, incluindo a altitude para calcular a diferença de consumos nas subidas e recupração nas descidas
	string name;
	double latitude; //in radians
	double longitude; //in radians
	double altitude;
	bool visited;
	vector<Edge *> adj_in;
	vector<Edge *> adj_out;
	bool chargingPoint = false;
	double dist = 0;
	Node *path = NULL;

public:
	int queueIndex = 0;
	friend class Graph;
	friend class Edge;

	/**
	 * @brief Node constructor without altitude, for testing.
	 * @param id id
	 * @param latitude latitude
	 * @param longitude longitude
	 */
	Node(string id, double latitude, double longitude) {
		this->id = id;
		this->latitude = latitude;
		this->longitude = longitude;
		this->altitude = 0;
		visited = false;
	}

	/**
	 * @brief Node constructor.
	 * @param id i
	 * @param y latitude
	 * @param y longitude
	 * @param z altitude
	 */
	Node(string i, double x, double y, double z) {
		id = i;
		latitude = x;
		longitude = y;
		altitude = z;
		name = "";
		visited = false;
	}

	/**
	 * @return id
	 */
	string getId() {
		return id;
	}

	/**
	 * @return longitude
	 */
	double getLong() {
		return longitude;
	}

	/**
	 * @return latitude
	 */
	double getLat() {
		return latitude;
	}

	/**
	 * @return altitude
	 */
	double getAlt() {
		return altitude;
	}

	/**
	 * @return dist
	 */
	double getDist() {
		return dist;
	}

	/**
	 * @return path
	 */
	Node* getPath() {
		return path;
	}

	/**
	 * @return adj_in
	 */
	vector<Edge *> getAdjIn() {
		return adj_in;
	}

	/**
	 * @return adj_out
	 */
	vector<Edge *> getAdjOut() {
		return adj_out;
	}

	/**
	 * @return chargingPoint
	 */
	bool getChargingPoint() {
		return chargingPoint;
	}

	/**
	 * @brief sets charging point
	 * @param b is charging point?
	 */
	void setChargingPoint(bool b) {
		chargingPoint = b;
	}

	/**
	 * @brief Add entry edge
	 * @param e1 edge
	 */
	void addEdgeIn(Edge* e1) {
		adj_in.push_back(e1);
	}

	/**
	 * @brief Add exit edge
	 * @param e1 edge
	 */
	void addEdgeOut(Edge* e1) {
		adj_out.push_back(e1);
	}

	/**
	 * @brief Equals operator
	 * @param n1 second edge
	 * @return if they are the same
	 */
	bool operator==(const Node n1){
		return (n1.id == this->id);
	}

	/**
	 * @brief < operator
	 * @param n1 second edge
	 * @return irrelevent value, only necessary for MutablePriorityQueue
	 */
	bool operator<(const Node n1){
		return (n1.id == this->id);
	}
};

class Road {

private:
	string id; ///< Unique Id of the road
	std::string name; ///< Name of the road
	bool twoWay; ///< True if road has two ways, false if it only has one.
	vector<Node *> nodesRoad;
public:
	friend class Graph;

	/**
	 * @brief Road constructor
	 * @param i id
	 * @param n name
	 * @param t twoWay
	 */
	Road(string i, std::string n, bool t) {
		id = i;
		name = n;
		twoWay = t;
	}

	/**
	 * @return id
	 */
	string getId() {
		return id;
	}

	/**
	 * @return name
	 */
	string getName() {
		return name;
	}

	/**
	 * @brief Equals operator
	 * @param n1 second edge
	 * @return if they are the same
	 */
	bool operator==(const Road n1){
		return (n1.id == this->id);
	}

	/**
	 * @brief Fill nodesRoad with nodes that belong to the road
	 */

	void fillNodes(vector<Node *> nodes) {

		bool added = false;

		for (int i = 0; i < nodes.size(); i++) {
			for (int j = 0; j < nodes[i]->getAdjIn().size(); j++) {
				if (nodes[i]->getAdjIn()[j]->getRoadId() == this->id) {
					nodesRoad.push_back(nodes[i]);
					added = true;
					break;
				}
			}

			if (!added) {
				for (int j = 0; j < nodes[i]->getAdjOut().size(); j++) {
					if (nodes[i]->getAdjOut()[j]->getRoadId() == this->id) {
						nodesRoad.push_back(nodes[i]);
						break;
					}
				}
			}
		}

		added = false;
	}

};

class Graph {
private:
	vector<Road*> roads;
	vector<Edge*> edges;
	vector<Node*> nodes;
	vector<Node*> chargingPoints;
public:
	/**
	 * Graph constructor.
	 */
	Graph() {
	}

	/**
	 * @return roads
	 */
	vector<Road*> getRoads() {
		return roads;
	}

	vector<Edge*> getEdges() {
		return edges;
	}

	vector<Node*> getNodes() {
		return nodes;
	}

	/**
	 * @param id id
	 * @returns node with certain id
	 */
	Node* findNode(string id){
		for(auto it = nodes.begin(); it != nodes.end(); it++){
			if((*it)->id == id){
				return (*it);
			}
		}
		return NULL;
	}

	/**
	 * @param id id
	 * @returns edge with certain id
	 */
	Edge* findEdge(string dep, string dest) {
		for(auto it = edges.begin(); it != edges.end(); it++){
			if((*it)->getSourceId() == dep && (*it)->getDestId() == dest){
				return (*it);
			}
		}
		return NULL;
	}

	/**
	 * @param id id
	 * @returns road with certain id
	 */
	Road* findRoad(string id) {
		for(auto it = roads.begin(); it != roads.end(); it++){
			if((*it)->id == id){
				return (*it);
			}
		}
		return NULL;
	}

	/**
	 * @brief Adds node to graph
	 * @param node node
	 * @return if it was added
	 */
	bool addNode(Node* node){
		for(auto it = nodes.begin(); it != nodes.end(); it++) {
			if ((*it)==node)
				return false;
		}
		nodes.push_back(node);
		return true;
	}

	/**
	 * @brief Adds edge to graph
	 * @param egde edge
	 * @return if it was added
	 */
	bool addEdge(Edge* edge){
		for(auto it = edges.begin(); it != edges.end(); it++) {
			if ((*it)==edge)
				return false;
		}
		edges.push_back(edge);
		return true;
	}

	/**
	 * @brief Adds road to graph
	 * @param road road
	 * @return if it was added
	 */
	bool addRoad(Road* road){
		for(auto it = roads.begin(); it != roads.end(); it++) {
			if ((*it)==road)
				return false;
		}
		roads.push_back(road);
		return true;
	}

	/**
	 * @return chargingPoints
	 */
	vector<Node*> getChargingPoints() {
		return chargingPoints;
	}

	/**
	 * @brief sets charging points based on the ones with more entry points
	 */
	void setChargingPoints() {

		int max;
		int max_index;

		//for (int i = 0; i < 5; i++) {
			max = 0;
			max_index = 0;

			for (int j = 0; j < nodes.size(); j++) {
				if(nodes[j]->adj_in.size() > max && !(nodes[j]->chargingPoint)) {
					max = nodes[j]->adj_in.size();
					max_index = j;
				}
			}

			nodes[max_index]->chargingPoint = true;
			chargingPoints.push_back(nodes[max_index]);
		//}
	}

	/**
	* @brief Initializes single-source shortest path data (path, dist).
	* @brief Used by all single-source shortest path algorithms.
	* @param id content of the source vertex and returns a pointer to the source vertex.
	* @return node
	*/

	Node * initSingleSource(const string id) {
		for (auto v : nodes) {
			v->dist = INF;
			v->path = nullptr;
		}
		auto s = findNode(id);
		s->dist = 0;
		return s;
	}

	/**
	* @brief Analyzes an edge in single-source shortest path algorithm.
	* @brief Used by all single-source shortest path algorithms.
	* @param v Node 1
	* @param w Node 2
	* @param weight value
	* @return Returns true if the target vertex was relaxed (dist, path).
	*/
	bool relax(Node *v, Node *w, double weight) {
		if (v->dist + weight < w->dist) {
			w->dist = v->dist + weight;
			w->path = v;
			return true;
		}
		else
			return false;
	}

	/**
	* @brief Dijkstra algorithm.
	* @param origin origin node
	*/
	void dijkstraShortestPath(const string origin) {
		auto s = initSingleSource(origin);
		MutablePriorityQueue<Node> q;
		q.insert(s);
		while ( ! q.empty() ) {
			auto v = q.extractMin();
			for (auto e : v->adj_out) {
				auto oldDist = findNode(e->destID)->dist;
				if (relax(v, findNode(e->destID), e->value)) {
					if (oldDist == INF)
						q.insert(findNode(e->destID));
					else
						q.decreaseKey(findNode(e->destID));
				}
			}
		}
	}

	/**
	 * @brief Calls Dijkstra algorithm with origin
	 * @param origin origin
	 * @param dest destination
	 * @return Vector with path from origin to destination
	 */
	vector<string> getShortestPath(string origin, string dest) {

		dijkstraShortestPath(origin);

		vector<string> res;
		auto v = findNode(dest);
		if (v == nullptr || v->dist == INF) // missing or disconnected
			return res;
		for ( ; v != nullptr; v = v->path)
			res.push_back(v->id);
		reverse(res.begin(), res.end());
		return res;
	}


	/**
	 * @brief Fills every road's node vector
	 */
	void organizeNodes() {
		for (int i = 0; i < roads.size(); i++) {
			roads[i]->fillNodes(nodes);
		}
	}

};
#endif /* SRC_GRAPH_H_ */
