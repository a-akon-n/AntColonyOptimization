#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Ant {
private:
	int id, start, position;
	double Pheromone;

	// tabu - list of visited nodes
	vector<int> tabu;
public:
	Ant();
	Ant(const Ant& ant);
	Ant(int id, int start, int position, double Pheromone, vector<int> tabu);
	~Ant();

	// method to return the id of the ant
	int getID();

	// method to return the id of the starting node of the ant
	int getStart();
	// method to set the id of the starting node of the ant
	void setStart(int id);

	// method to return the id of the current node of the ant
	int getPosition();
	// method to set the id of the current node of the ant
	void setPosition(int id);

	// method to return the amount of pheromone the ant has
	double getPheromone();
	// method to set the am0ount of pheromone the ant has
	void setPheromone(double pheromone);

	// method to add a visited node to the tabuu list
	void addTabu(int id);

	// method to clear the contents of the tabu list
	void clearTabu();

	// method to return the tabu list
	vector<int> getTabu();

	// method to check if an ant visited 2 nodes before
	bool visited(int id);

	Ant& operator=(const Ant& ant);
	bool operator==(const Ant& a);
	friend ostream& operator<<(ostream& os, const Ant& a);
};
