/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <cfloat>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited = false;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue
	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

	//É preciso as coordenadas dos pontos, incluindo a altitude para calcular a diferença de consumos nas subidas e recupração nas descidas


	string name;
	double latitude = 0; //in radians
	double longitude = 0; //in radians
	double altitude = 0;
	bool chargingPoint = false;



public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;

	Vertex<T>(T info, double latitude, double longitude) {
			this->info = info;
			this->latitude = latitude;
			this->longitude = longitude;
			this->altitude = 0;
		}

		Vertex<T>(T info, double x, double y, double z) {
			this->info = info;
			latitude = x;
			longitude = y;
			altitude = z;
			name = "";
		}

		Vertex<T>(T info, double x, double y, double z, string n) {
			this->info = info;
			latitude = x;
			longitude = y;
			altitude = z;
			name = n;
		}


};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}



/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	unsigned long roadID;
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w, unsigned long r);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, unsigned long r): dest(d), weight(w), roadID(r) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	// TODO
	int i, j;
	Vertex<T> *v, *w;
	MutablePriorityQueue<Vertex<T> > q;

	for(i=0; i<this->vertexSet.size(); i++){
		this->vertexSet.at(i).dist = DBL_MAX;
		this->vertexSet.at(i).path = NULL;
	}
	origin->dist = 0;

	q.insert(origin);

	while(!q.empty()){
		v = q.extractMin();
		for(j=0; j < v->adj.size();j++){
			w = v->adj.at(j);

			if(w->getDist() > (v->getDist() + v->adj.at(j).weight)){
				w->dist = v->dist + v->adj.at(j).weight;
				w->path = v;
				if(w->dist == DBL_MAX){
					q.insert(w);
				}
				else{
					q.decreaseKey(w);
				}
			}
		}

	}



	vector<Vertex<T>*> vertexSet = Graph<T>::getVertexSet();

		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			vertexSet.at(i)->dist = DBL_MAX;
			vertexSet.at(i)->path = NULL;
		}

		//MutablePriorityQueue<Vertex<T> > q;
		Vertex<T>* v1 = findVertex(origin);
		v1->setDist(0);
		q.insert(v1);

		while (!q.empty()) {
			Vertex<T>* v = q.extractMin();
			vector<Edge<T> > adj = v->adj;

			for (unsigned int i = 0; i < adj.size(); i++) {
				double dist = adj.at(i).dest->getDist();
				if (dist > v->getDist() + adj.at(i).weight) {
					adj.at(i).dest->setDist(v->getDist() + adj.at(i).weight);
					adj.at(i).dest->setPath(v);

					if (dist != DBL_MAX)
						q.decreaseKey(adj.at(i).dest);
					else
						q.insert(adj.at(i).dest);

				}

			}
		}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	// TODO
	Vertex<T> * v;
	v = findVertex(dest);
	while(v != *findVertex(origin)){
		res.push_back(v->info);
		v = v->path;

	}

	res.push_back(origin.info);

	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	// TODO
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
