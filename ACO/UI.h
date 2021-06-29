#pragma once
#include "ServiceAnt.h"
#include "AntColonyOptimization.h"

class UserInterface {
private:
	ServiceAnt srvA;
	ACO aco;

	void PrintMenu();
	void addAnt();
	void addKAnt();
	void deleteAnt();
	void updateAnt();
	void printAnts();
	void loadAnts();

	void loadG();
	void printG();

	void setACO();
	void runACO();




public:
	UserInterface();
	UserInterface(ServiceAnt& srvA, ACO& aco);
	~UserInterface();

	void runConsole();

}; #pragma once
