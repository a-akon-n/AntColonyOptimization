#pragma once
#include <fstream>
#include "Repository.h"
#include "Ant.h"

class RepoFile : public Repo {
private:
	string filename;
public:
	RepoFile();
	RepoFile(string filename);
	~RepoFile();

	// method to load the ant data from a text file
	void load_from_file();
	// method to write the ant data to a text file
	void write_to_file();
};


inline RepoFile::RepoFile()
{
	this->filename = "";
}

inline RepoFile::RepoFile(string filename)
{
	this->filename = filename;
}

inline RepoFile::~RepoFile()
{
}

inline void RepoFile::load_from_file()
{
	ifstream in(this->filename);
	int nr;
	in >> nr;
	for (int i = 0; i < nr; i++) {
		int id, start, position;
		double pheromone;
		vector<int> tabu;
		tabu.resize(0);
		in >> id >> start >> position >> pheromone;
		Ant a(id, start, position, pheromone, tabu);
		this->addElem(a);
	}
	in.close();
}


inline void RepoFile::write_to_file()
{
	ofstream out(this->filename);
	out << this->repo.size() << endl;
	for (int i = 0; i < this->repo.size(); i++) {
		out << this->repo[i].getID() << endl << this->repo[i].getStart() << endl << this->repo[i].getPosition() << endl << this->repo[i].getPheromone() << endl;
	}
	out.close();
}

