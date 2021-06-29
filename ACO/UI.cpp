#include <cstdlib>
#include "UI.h"
#include "MyException.h"

void UserInterface::PrintMenu()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "x. Close" << endl;
	cout << "addA. Add Ant" << endl;
	cout << "delA. Delete Ant" << endl;
	cout << "upA. Update Ant" << endl;
	cout << "printA. Show all Ants" << endl;
	cout << "add_kA. Adds k random Ants (X)" << endl;
	cout << "loadG. Loads the list of nodes and edges from file" << endl;
	cout << "printG. Prints the Graph to the screen" << endl;
	cout << "ACO. Runs the Ant Colony Optimization Algorithm" << endl;
	cout << "setACO. Changes the default parameters of the ACO Algorithm" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void UserInterface::addAnt()
{
	int id, start, position;
	double pheromone;
	vector<int> tabu;
	tabu.resize(0);

	cout << "Give the ID of the ant: ";
	cin >> id;
	cout << "Give the starting node of the ant: ";
	cin >> start;
	position = start;
	cout << "Give the quantity of pheromones of the ant between (0,1): ";
	cin >> pheromone;
	try {
		this->srvA.addAnt(id, start, position, pheromone, tabu);
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}
}

void UserInterface::addKAnt()
{
	int k;
	cout << "Give the number of ants to add randomly: ";
	cin >> k;
	try {
		for (int i = 0; i < k; i++) {
			int n = this->aco.graph.get_N_node();
			if (n == 0) {
				throw MyException("Can't divide by 0! \n");
			}
			int id = this->srvA.getSizeAnt() + k, start = (int)rand() % n;
			double pheromone = (double)rand() / RAND_MAX;
			vector<int> tabu;
			this->srvA.addAnt(id, start, start, pheromone, tabu);
		}
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}
}

void UserInterface::deleteAnt()
{
	int id;
	cout << "Give the id of the ant to delete: ";
	cin >> id;
	try {
		this->srvA.deleteAnt(id);
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}
}

void UserInterface::updateAnt()
{
	int id, start, position;
	double pheromone;
	vector<int> tabu;
	tabu.resize(0);

	cout << "Give the ID of the and to update: ";
	cin >> id;
	cout << "Give the new starting node of the ant: ";
	cin >> start;
	position = start;
	cout << "Give the new quantity of pheromones of the ant between (0,1): ";
	cin >> pheromone;
	Ant ant(id, start, position, pheromone, tabu);
	try {
		this->srvA.updateAnt(id, ant);
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}
}

void UserInterface::printAnts()
{
	for (int i = 0; i < this->srvA.getSizeAnt(); i++) {
		cout << this->srvA.getAnt(i + 1) << endl;
	}
}

void UserInterface::loadAnts()
{
	this->srvA.loadAnt();
}

void UserInterface::loadG()
{
	this->aco.loadGraph();
}

void UserInterface::printG()
{
	this->aco.printGraph();
}

void UserInterface::setACO()
{
	int iterations, alpha, betha, Q;
	double rho;
	cout << "N.o. of iterations - how many times the simulation runs: " << this->aco.getIterations() << endl;
	cout << "Insert a new value or insert the default again: ";
	try {
		cin >> iterations;
		if (iterations <= 0) {
			throw MyException("Number of iterations is lower or equal to 0 \n");
		}
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}

	cout << "Alpha - influences an ant's tendency to follow the path based on its pheromones: " << this->aco.getAlpha() << endl;
	cout << "Insert a new value between [1, 15] or insert the default again: ";
	try {
		cin >> alpha;
		if (alpha < 1 || alpha>15) {
			throw MyException("Alpha is greater than 15 or lower than 1\n");
		}
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}

	cout << "Betha - influences an ant's tendency to follow the path based on its length: " << this->aco.getBetha() << endl;
	cout << "Insert a new value between [1, 15] or insert the default again: ";
	try {
		cin >> betha;
		if (betha < 1 || betha>15) {
			throw MyException("Betha is greater than 15 or lower than 1\n");
		}
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}

	cout << "Q - constant value for computing the deposited ammount of pheromones: " << this->aco.getQ() << endl;
	cout << "Insert a new value between [1, 10] or insert the default again: ";
	try {
		cin >> Q;
		if (Q < 1 || Q>10) {
			throw MyException("Q is greater than 10 or lower than 1\n");
		}
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}

	cout << "Rho - the pheromone evaporation coefficient" << this->aco.getRho() << endl;
	cout << "Insert a new value between (0, 0.5] or insert the default again: ";
	try {
		cin >> rho;
		if (rho <= 0 || rho > 0.5) {
			throw MyException("Rho is greater than 0.5 or lower or equal to0\n");
		}
	}
	catch (MyException& e) {
		cout << e.toString() << endl;
	}

	this->aco.setACO(iterations, alpha, betha, rho, Q);
}

void UserInterface::runACO()
{
	vector<int> path = this->aco.runACO();
	this->aco.printPath(path);
}


UserInterface::UserInterface()
{
}

UserInterface::UserInterface(ServiceAnt& srvA, ACO& aco)
{
	this->srvA = srvA;
	this->aco = aco;
}

UserInterface::~UserInterface()
{
}

void UserInterface::runConsole()
{
	string option;
	while (true) {
		this->PrintMenu();
		cout << "Alegeti optiunea: ";
		cin >> option;
		if (option == "x")break;
		else if (option == "addA") {
			this->addAnt();
		}
		else if (option == "addKA") {
			this->addKAnt();
		}
		else if (option == "delA") {
			this->deleteAnt();
		}
		else if (option == "upA") {
			this->updateAnt();
		}
		else if (option == "printA") {
			this->printAnts();
		}
		else if (option == "loadG") {
			this->loadG();
		}
		else if (option == "printG") {
			this->printG();
		}
		else if (option == "setACO") {
			this->setACO();
		}
		else if (option == "ACO") {
			this->runACO();
		}
		else {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "Choose another option!!!" << endl;
		}
	}
}
