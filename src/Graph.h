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
	static int next_edge_id; ///< static variable to know the next unique edge ID.
	int edgeID; ///< unique id of the edge.

};

class Node {

private:
	unsigned long id; ///< Node ID
	//É preciso as coordenadas dos pontos, incluindo a altitude para calcular a diferença de consumos nas subidas e recupração nas descidas
	string name;
	double latitude; //in radians
	double longitude; //in radians
	double x_coor;
	double y_coor;
	double z_coor;

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
		x_coor = x;
		y_coor = y;
		z_coor = z;
		name = "";
	}

	Node(long i, double x, double y, double z, string n) {
		id = i;
		x_coor = x;
		y_coor = y;
		z_coor = z;
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
	Node* findNode(int id){
		for(int i=0; i < nodes.size(); i++){
			if(nodes[i].id == id){
				return &nodes[i];
			}

		}
		return NULL;
	};
	Node* findNode(string name){
		for(int i=0; i < nodes.size(); i++){
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



};
#endif /* SRC_GRAPH_H_ */
