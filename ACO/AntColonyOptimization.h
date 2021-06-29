#pragma once
#include "Graph.h"
#include "ServiceAnt.h"

class ACO {
public:
	Graph graph;
private:
	ServiceAnt srvA;
	int alpha, betha, Q = 1, iterations;
	double rho;
public:
	ACO();
	ACO(const Graph& graph, const ServiceAnt& srvA, int iterations, int alpha, int betha, double rho, int Q = 1);
	~ACO();

	void setAlpha(int val);
	int getAlpha();

	void setBetha(int val);
	int getBetha();

	void setRho(double val);
	double getRho();

	void setQ(int val);
	int getQ();

	void setIterations(int val);
	int getIterations();


	// main method that runs the simulation
	vector<int> runACO();

	// method to generate the paths for each ant
	// paths - int, vector of arrays that saves the id's for each 
	void generateSolution(vector<vector<int>>& paths);

	// method to select a random edge between the neighbours of the current node that
	//	the ant is positioned on; it finds the probability of each route 
	//	and also introduces a random element to determine the new route it chooses
	int edgeSelection(Ant antk);

	// updates the ammount of pheromones on the path of the ant that completed a cycle
	void pheromoneUpdateLocal(vector<int> path, Ant antk);

	// updates the ammount of pheromones after all the ants completed one iteration by evaporation
	void pheromoneUpdateGlobal();

	// method that returns the best route in terms of efficiency
	int bestRoute(vector<vector<int>> paths);

	// returns the full distance of the path that an ant has completed in one iteration
	int getPathDistance(vector<int> path);

	// method to emtpy the contents of the paths
	void clearPath(vector<vector<int>>& paths);

	// prints the best path to the screen
	void printPath(vector<int> path);

	// prints the graph to the screen
	void printGraph();

	// loads the list of nodes and edges from a file
	void loadGraph();

	// changes the values and parameters of the ACO algorithm
	void setACO(int iterations, int alpha, int betha, double rho, int Q);

};