#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node;
class Edge;
class Road;

class Edge {
private:
	unsigned long roadID;
	unsigned long destID; //next unique edge ID.
	unsigned long sourceID; // unique id of the edge.

public:
	Edge(unsigned long roadid, unsigned long idsource, unsigned long iddest) {
		roadID = roadid;
		sourceID = idsource;
		destID = iddest;
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
	bool chargingPoint;

public:
	friend class Graph;
	friend class Edge;
	Node(unsigned long id, double latitude, double longitude) {
		this->id = id;
		this->latitude = latitude;
		this->longitude = longitude;
	}

	Node(long i, double x, double y, double z) {
		id = i;
		latitude = x;
		longitude = y;
		altitude = z;
		name = "";
	}

	Node(long i, double x, double y, double z, string n) {
		id = i;
		latitude = x;
		longitude = y;
		altitude = z;
		name = n;
	}

	bool operator==(const Node n1){
		return (n1.id == this->id);
	}

};

class Road {

private:
	unsigned long id; ///< Unique Id of the road
	std::string name; ///< Name of the road
	bool twoWay; ///< True if road has two ways, false if it only has one.

};

class Graph {
private:
	vector<Road> roads;
	vector<Edge> edges;
	vector<Node> nodes;
public:
	Graph();
	Node* findNode(unsigned long id){
		for(auto it = nodes.begin(); it != nodes.end(); it++){
			if((*it).id == id){
				return &(*it);
			}

		}
		return NULL;
	};
	Node* findNode(string name){
		for(unsigned int i=0; i < nodes.size(); i++){
					if(nodes[i].name == name){
						return &nodes[i];
					}

				}
				return NULL;
	}

	bool addNode(Node node){
		for(auto it = nodes.begin(); it != nodes.end(); it++) {
			if ((*it)==node)
				return false;
		}
		nodes.push_back(node);
		return true;
	}

	bool addEdge(Edge edge){
		for(auto it = edges.begin(); it != edges.end(); it++) {
			if ((*it)==edge)
				return false;
		}
		edges.push_back(edge);
		return true;
	}



};
#endif /* SRC_GRAPH_H_ */
