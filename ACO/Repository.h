#pragma once
#include <vector>
#include "Ant.h"

using namespace std;

class Repo {
protected:
	vector<Ant> repo;
public:
	Repo();
	Repo(const vector<Ant>& repo);
	~Repo();

	// method to find wheteher an elem exists or not
	// returns 1 if found and -1 otherwise
	int find(const Ant& a);

	// method to return the size of the repo
	int getDimRepo();

	// method to return an element from the repo by id
	Ant getElem(int id);

	// method to return all the elements in the repo
	vector<Ant> getAll();

	// method to add a new element to the repo
	void addElem(Ant& elem);

	// method to delete an element from the repo usint the id
	void deleteElem(Ant elem);

	// method to update an old element with a new one
	void updateElem(Ant& nElem, Ant& oElem);


	Repo& operator=(const Repo& repo);
};

inline Repo::Repo()
{
	this->repo.reserve(0);
}

inline Repo::Repo(const vector<Ant>& repo)
{
	this->repo.reserve(repo.size());
	this->repo = repo;
}

inline Repo::~Repo()
{
	this->repo.clear();
	this->repo.resize(0);
}

inline int Repo::find(const Ant& a)
{
	for (int i = 0; i < this->getDimRepo(); i++) {
		if (this->repo[i] == a) {
			return 1;
		}
	}
	return -1;
}

inline int Repo::getDimRepo()
{
	return this->repo.size();
}


inline Ant Repo::getElem(int id)
{
	return this->repo[id - 1];
}

inline vector<Ant> Repo::getAll()
{
	return this->repo;
}

inline void Repo::addElem(Ant& elem)
{
	this->repo.push_back(elem);
}

inline void Repo::deleteElem(Ant elem)
{
	for (int i = 0; i < this->repo.size(); i++) {
		if (elem == this->repo[i]) {
			for (int j = i; j < this->repo.size() - 1; j++) {
				this->repo[j] = this->repo[j + 1];
			}
			this->repo.pop_back();
		}
	}
}

inline void Repo::updateElem(Ant& nElem, Ant& oElem)
{
	for (int i = 0; i < this->repo.size(); i++) {
		if (this->repo[i] == oElem) {
			this->repo[i] = nElem;
		}
	}
}


inline Repo& Repo::operator=(const Repo& repo)
{
	this->repo.clear();
	for (int i = 0; i < repo.repo.size(); i++) {
		this->repo.push_back(repo.repo[i]);
	}
	return *this;
}
