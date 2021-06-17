#include "Ant.h"

Ant::Ant()
{
	this->id = 0;
	this->start = 0;
	this->position = 0;
	this->Pheromone = 0.0;
	this->tabu.resize(0);
}

Ant::Ant(const Ant& ant)
{
	this->id = ant.id;
	this->start = ant.start;
	this->position = ant.position;
	this->Pheromone = ant.Pheromone;
	this->tabu.resize(ant.tabu.size());
	this->tabu = ant.tabu;
}

Ant::Ant(int id, int start, int position, double Pheromone, vector<int> tabu) {
	this->id = id;
	this->start = start;
	this->position = position;
	this->Pheromone = Pheromone;
	this->tabu.resize(tabu.size());
	this->tabu = tabu;
}

Ant::~Ant()
{
	this->id = 0;
	this->start = 0;
	this->position = 0;
	this->Pheromone = 0.0;
	this->tabu.clear();
	this->tabu.resize(0);
}

int Ant::getID()
{
	return this->id;
}

int Ant::getStart()
{
	return this->start;
}

void Ant::setStart(int id)
{
	this->start = id;
}

int Ant::getPosition()
{
	return this->position;
}

void Ant::setPosition(int id)
{
	this->position = id;
}

double Ant::getPheromone()
{
	return this->Pheromone;
}

void Ant::setPheromone(double pheromone)
{
	this->Pheromone = pheromone;
}

void Ant::addTabu(int id)
{
	this->tabu.push_back(id);
}

void Ant::clearTabu()
{
	this->tabu.clear();
}

vector<int> Ant::getTabu()
{
	return this->tabu;
}

bool Ant::visited(int id)
{
	for (int i = 0; i < this->tabu.size(); i++) {
		if (this->tabu[i] == id) return true;
	}
	return false;
}

Ant& Ant::operator=(const Ant& ant)
{
	if (this != &ant) {
		this->id = ant.id;
		this->start = ant.start;
		this->position = ant.position;
		this->Pheromone = ant.Pheromone;
		this->tabu.resize(ant.tabu.size());
		this->tabu = ant.tabu;
	}

	return *this;
}

bool Ant::operator==(const Ant& a)
{
	return (this->id == a.id) && (this->Pheromone == a.Pheromone) && (this->tabu == a.tabu);
}

ostream& operator<<(ostream& os, const Ant& a)
{
	os << "Furnica: " << a.id << " | Start: " << a.start << " | Pozitie: " << a.position << " | Feromoni: " << a.Pheromone;
	return os;
}
