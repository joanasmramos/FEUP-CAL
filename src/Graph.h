#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <iostream>
#include <vector>

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
	double x_coor;
	double y_coor;
	double z_coor;

public:
	friend class Graph;
	friend class Edge;
};

class Road {

private:
	unsigned long id; ///< Unique Id of the road
	std::string name; ///< Name of the road
	bool twoWay; ///< True if road has two ways, false if it only has one.

};

#endif /* SRC_GRAPH_H_ */
