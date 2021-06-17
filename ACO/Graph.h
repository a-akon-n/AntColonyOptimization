#pragma once
#include <iostream>
#include <vector>

using namespace std;

// structure to describe a node
// id - identificator of the node
struct Node {
	int id;
};

// structure to describe an edge
// src, dest - Node, represents the starting node and the ending node of an edge
// distance - intm represents the distance between the two nodes
// trailPheromone - float, the ammount of pheromone on the trail
struct Edge {
	Node src, dest;
	int distance;
	double trailPheromone = 1;
};

// class Graph to describe a graph
class Graph {
public:
	// adjList - the adjacency list that represents the graph
	vector<vector<Node>> adjList;
	// Nodes - vector of nodes
	vector<Node> Nodes;
	// Edges - vector of edges
	vector<Edge> Edges;
	// N - int, the number of nodes in the graph
	int N;
	string filenameN, filenameE;

public:
	// constructors
	Graph();
	Graph(const Graph& g);
	Graph(const vector<Node>& nodes, const vector<Edge>& edges, string filenameN, string filenameE);
	// destructor
	~Graph();

	// returns the number of nodes
	int get_N_node();

	// returns the number of edges
	int get_N_edge();

	// returns the node by id;
	Node get_node(int id);

	// returns the edge by source and destination nodes
	Edge get_edge(Node src, Node dest);

	// method to add a new edge to the graph
	// src, dest - Node, the starting node and ending node
	// distance - int, the distance between the 2 nodes
	void addEdge(const Edge& e);

	// method to add a new node to the graph
	// node - Node, a new node
	void addNode(const Node& node);

	// method to delete an existing node from the graph
	void deleteNode(Node n);

	// returns the immediate adjacent nodes of a given node
	vector<Node> getNeighbours(Node n);

	// equal operator
	Graph& operator=(const Graph& graph);

	//method to read nodes from file
	void load_from_file_nodes();
	//method to write nodes from file
	void save_to_file_nodes();

	//method to read edges from file
	void load_from_file_edges();
	//method to write edges from file
	void save_to_file_edges();
};