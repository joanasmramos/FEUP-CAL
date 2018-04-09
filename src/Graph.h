#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "MutablePriorityQueue.h"

using namespace std;

class Node;
class Edge;
class Road;
class Graph;

#define INF numeric_limits<double>::max()

class Edge {
private:
	unsigned long roadID;
	unsigned long destID; //next unique edge ID.
	unsigned long sourceID; // unique id of the edge.
	double value; //size of the edge

public:
	Edge(unsigned long roadid, unsigned long idsource, unsigned long iddest) {
		roadID = roadid;
		sourceID = idsource;
		destID = iddest;
		value = INF;
	}

	unsigned long getDestId() const {
		return destID;
	}

	void setDestId(unsigned long destId) {
		destID = destId;
	}

	unsigned long getRoadId() const {
		return roadID;
	}

	void setRoadId(unsigned long roadId) {
		roadID = roadId;
	}

	unsigned long getSourceId() const {
		return sourceID;
	}

	void setSourceId(unsigned long sourceId) {
		sourceID = sourceId;
	}

	double getValue() {
		return value;
	}

	void setValue(double v) {
		value = v;
	}

	bool operator==(const Edge e1){
		return (e1.roadID == this->roadID);
	}
};

class Node {

private:
	unsigned long id; ///< Node ID
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
	Node(unsigned long id, double latitude, double longitude) {
		this->id = id;
		this->latitude = latitude;
		this->longitude = longitude;
		this->altitude = 0;
		visited = false;
	}

	Node(long i, double x, double y, double z) {
		id = i;
		latitude = x;
		longitude = y;
		altitude = z;
		name = "";
		visited = false;
	}

	Node(long i, double x, double y, double z, string n) {
		id = i;
		latitude = x;
		longitude = y;
		altitude = z;
		name = n;
		visited = false;
	}

	unsigned long getId() {
		return id;
	}

	double getLong() {
		return longitude;
	}

	double getLat() {
		return latitude;
	}

	double getAlt() {
		return altitude;
	}

	double getDist() {
		return dist;
	}

	Node* getPath() {
		return path;
	}

	void setDist(double d) {
		dist = d;
	}

	void setPath(Node* p) {
		path = p;
	}

	vector<Edge *> getAdjIn() {
		return adj_in;
	}

	bool getChargingPoint() {
		return chargingPoint;
	}

	void setChargingPoint(bool b) {
		chargingPoint = b;
	}

	void addEdgeIn(Edge* e1) {
		adj_in.push_back(e1);
	}

	void addEdgeOut(Edge* e1) {
		adj_out.push_back(e1);
	}

	bool operator==(const Node n1){
		return (n1.id == this->id);
	}

	bool operator<(const Node n1){
		return (n1.id == this->id);
	}
};

class Road {

private:
	unsigned long id; ///< Unique Id of the road
	std::string name; ///< Name of the road
	bool twoWay; ///< True if road has two ways, false if it only has one.
public:
	Road(unsigned long i, std::string n, bool t) {
		id = i;
		name = n;
		twoWay = t;
	}

	bool operator==(const Road n1){
		return (n1.id == this->id);
	}

};

class Graph {
private:
	vector<Road*> roads;
	vector<Edge*> edges;
	vector<Node*> nodes;

public:
	Graph();

	Node* findNode(unsigned long id){
		for(auto it = nodes.begin(); it != nodes.end(); it++){
			if((*it)->id == id){
				return (*it);
			}

		}
		return NULL;
	}

	Edge* findEdge(unsigned long dep, unsigned long dest) {
		for(auto it = edges.begin(); it != edges.end(); it++){
			if((*it)->getSourceId() == dep && (*it)->getDestId() == dest){
				return (*it);
			}
		}
		return NULL;
	}


	bool addNode(Node* node){
		for(auto it = nodes.begin(); it != nodes.end(); it++) {
			if ((*it)==node)
				return false;
		}
		nodes.push_back(node);
		return true;
	}

	bool addEdge(Edge* edge){
		for(auto it = edges.begin(); it != edges.end(); it++) {
			if ((*it)==edge)
				return false;
		}
		edges.push_back(edge);
		return true;
	}

	bool addRoad(Road* road){
		for(auto it = roads.begin(); it != roads.end(); it++) {
			if ((*it)==road)
				return false;
		}
		roads.push_back(road);
		return true;
	}

	void setChargingPoints() {

		int max;
		int max_index;

		for (int i = 0; i < 5; i++) {
			max = 0;
			max_index = 0;
			for (int j = 0; j < nodes.size(); j++) {
				if(nodes[j]->getAdjIn().size() > max && !(nodes[j]->getChargingPoint())) {
					max = nodes[j]->getAdjIn().size();
					max_index = j;
				}
			}

			nodes[max_index]->setChargingPoint(true);
		}
	}

	/**
	* Initializes single-source shortest path data (path, dist).
	* Receives the content of the source vertex and returns a pointer to the source vertex.
	* Used by all single-source shortest path algorithms.
	*/

	Node * initSingleSource(const unsigned long id) {
		for (auto v : nodes) {
			v->setDist(INF);
			v->setPath(nullptr);
		}
		auto s = findNode(id);
		s->setDist(0);
		return s;
	}

	/**
	* Analyzes an edge in single-source shortest path algorithm.
	* Returns true if the target vertex was relaxed (dist, path).
	* Used by all single-source shortest path algorithms.
	*/
	bool relax(Node *v, Node *w, double weight) {
		if (v->getDist() + weight < w->getDist()) {
			w->setDist(v->getDist() + weight);
			w->setPath(v);
			return true;
		}
		else
			return false;
	}

	/**
	* Dijkstra algorithm.
	*/
	void dijkstraShortestPath(const unsigned long origin) {
		auto s = initSingleSource(origin);
		MutablePriorityQueue<Node> q;
		q.insert(s);
		while ( ! q.empty() ) {
			auto v = q.extractMin();
			for (auto e : v->adj_out) {
				auto oldDist = findNode(e->getDestId())->dist;
				if (relax(v, findNode(e->getDestId()), e->getValue())) {
					if (oldDist == INF)
						q.insert(findNode(e->getDestId()));
					else
						q.decreaseKey(findNode(e->getDestId()));
				}
			}
		}
	}

	vector<unsigned long> getShortestPath(unsigned long origin, unsigned long dest) {

		dijkstraShortestPath(origin);

		vector<unsigned long> res;
		auto v = findNode(dest);
		if (v == nullptr || v->getDist() == INF) // missing or disconnected
			return res;
		for ( ; v != nullptr; v = v->getPath())
			res.push_back(v->getId());
		reverse(res.begin(), res.end());
		return res;
	}


};
#endif /* SRC_GRAPH_H_ */
