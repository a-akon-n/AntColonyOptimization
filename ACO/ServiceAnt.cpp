#include "ServiceAnt.h"
#include "MyException.h"

ServiceAnt::ServiceAnt()
{
}

ServiceAnt::ServiceAnt(const RepoFile& ants)
{
	this->repoAnt = ants;
}

ServiceAnt::~ServiceAnt()
{
}

void ServiceAnt::addAnt(int id, int start, int position, double pheromone, vector<int> tabu) throw(MyException)
{
	Ant a(id, start, position, pheromone, tabu);
	this->validAnt.validateAnt(a);
	if (this->repoAnt.find(a) == 1) {
		throw MyException("Furnicea nu poate fi adaugata deoarece deja exista! \n");
	}
	this->repoAnt.addElem(a);
	this->repoAnt.write_to_file();
}

void ServiceAnt::deleteAnt(int id) throw(MyException)
{
	int i = this->repoAnt.getDimRepo();
	while (i != 0) {
		if (this->repoAnt.getElem(i).getID() == id) {
			id = i;
			break;
		}
	}
	if (this->repoAnt.find(this->repoAnt.getElem(id)) == -1) {
		throw MyException("Produsul nu se poate sterge deoarece nu exista! \n");
	}
	this->repoAnt.deleteElem(this->repoAnt.getElem(id));
	this->repoAnt.write_to_file();
}


void ServiceAnt::updateAnt(int id, Ant nA) throw(MyException)
{
	Ant a = this->getAnt(id);
	this->validAnt.validateAnt(nA);
	if (this->repoAnt.find(a) == -1) {
		throw MyException("Produsul nu poate fi actualizat deoarece nu exista! \n");
	}
	this->repoAnt.updateElem(nA, a);
	this->repoAnt.write_to_file();
}

void ServiceAnt::loadAnt()
{
	this->repoAnt.load_from_file();
}

int ServiceAnt::getSizeAnt()
{
	return this->repoAnt.getDimRepo();
}

Ant ServiceAnt::getAnt(int id)
{
	return this->repoAnt.getElem(id);
}

vector<Ant> ServiceAnt::getAllAnt()
{
	return this->repoAnt.getAll();
}
