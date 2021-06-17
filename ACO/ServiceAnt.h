#pragma once
#include "FileRepository.h"
#include "ValidatorAnt.h"

class ServiceAnt {
private:
	RepoFile repoAnt;
	Validator validAnt;
public:
	ServiceAnt();
	ServiceAnt(const RepoFile& ants);
	~ServiceAnt();

	// method to add an element to the repo
	// id - Integer, the id of the ant
	// start - Integer, the starting position of the ant
	// position - Integer, the current position of the ant
	// pheromone - Double, the ammount of pheromone an ant has
	// tabu - vector<Integer>- contains the list of visited cities
	void addAnt(int id, int start, int position, double pheromone, vector<int> tabu);

	// method to delete an Ant by id
	void deleteAnt(int id);

	// method to update an Ant using the id with a new Ant
	void updateAnt(int id, Ant nA);

	// method to load the data from a file
	void loadAnt();

	// method to return the number of Ants
	int getSizeAnt();

	// method to return and Ant by id
	Ant getAnt(int id);

	// method to return all Ants
	vector<Ant> getAllAnt();
};