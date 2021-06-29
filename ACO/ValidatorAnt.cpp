#include "ValidatorAnt.h"
#include "MyException.h"

Validator::Validator()
{
}

Validator::~Validator()
{
}

void Validator::validateAnt(Ant& ant)
{
	string errorMessage = "";
	if (ant.getStart() != (int)ant.getStart()) {
		errorMessage += "The ID of the ant's start node is not integer! \n";
	}
	if (ant.getStart() < 0) {
		errorMessage += "The ID of tha ant's start node can't be negative! \n";
	}
	if (ant.getPosition() != (int)ant.getPosition()) {
		errorMessage += "The ID of the ant's current node is not integer! \n";
	}
	if (ant.getPosition() < 0) {
		errorMessage += "The ID of the and't current node can't be negative! \n";
	}
	if (ant.getPheromone() != (double)ant.getPheromone()) {
		errorMessage += "The quantiti of pheromones is not a double! \n";
	}
	if (ant.getPheromone() == 0) {
		errorMessage += "The quantity of pheromones can't be null! \n";
	}
	else if (ant.getPheromone() < 0) {
		errorMessage += "The quantity of pheromones can't be negativ! \n";
	}
}
