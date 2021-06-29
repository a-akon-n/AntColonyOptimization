#include "AntColonyOptimization.h"
#include <cstdlib>
#include <math.h>


ACO::ACO()
{
	this->iterations = 50;
	this->alpha = 1;
	this->betha = 1;
	this->rho = 0.1;
}

ACO::ACO(const Graph& graph, const ServiceAnt& srvA, int iterations, int alpha, int betha, double rho, int Q)
{
	this->graph = graph;
	this->srvA = srvA;
	this->iterations = iterations;
	this->alpha = alpha;
	this->betha = betha;
	this->rho = rho;
	this->Q = Q;
}

ACO::~ACO()
{
	this->iterations = 50;
	this->alpha = 1;
	this->betha = 1;
	this->rho = 0.1;
}

void ACO::setAlpha(int val)
{
	this->alpha = val;
}

int ACO::getAlpha()
{
	return this->alpha;
}

void ACO::setBetha(int val)
{
	this->betha = val;
}

int ACO::getBetha()
{
	return this->betha;
}

void ACO::setRho(double val)
{
	this->rho = val;
}

double ACO::getRho()
{
	return this->rho;
}

void ACO::setQ(int val)
{
	this->Q = val;
}

int ACO::getQ()
{
	return this->Q;
}

void ACO::setIterations(int val)
{
	this->iterations = val;
}

int ACO::getIterations()
{
	return this->iterations;
}

vector<int> ACO::runACO()
{
	vector<vector<int>> paths;
	vector<vector<int>> bestPath;
	int id = -1, min = 1000000;
	paths.resize(this->srvA.getSizeAnt());
	for (int i = 0; i < this->getIterations(); i++) {
		this->generateSolution(paths);
		id = this->bestRoute(paths);
		bestPath.push_back(paths[id]);
		this->printPath(paths[id]);
		this->pheromoneUpdateGlobal();
		id = -1;
		this->clearPath(paths);
	}
	int distance[100] = { 0 };
	for (int i = 0; i < bestPath.size(); i++) {
		distance[this->getPathDistance(bestPath[i])] += 1;
	}
	int i = 0;
	min = 0;
	while (i < 100) {
		if (distance[i] == 0) {
			i++;
			continue;
		}
		min = i;
		break;
	}
	i = 0;
	cout << endl;
	while (i < bestPath.size()) {
		if (min == this->getPathDistance(bestPath[i])) {
			break;
		}
		i++;
	}
	return bestPath[i];
}

void ACO::generateSolution(vector<vector<int>>& paths)
{
	for (int i = 0; i < this->srvA.getSizeAnt(); i++) {
		Ant antk = this->srvA.getAllAnt()[i];
		antk.addTabu(antk.getPosition());

		// find a path for each ant randomly
		while (antk.getTabu().size() != this->graph.get_N_node()) {
			antk.addTabu(edgeSelection(antk));
			antk.setPosition(antk.getTabu().back());
			this->srvA.updateAnt(i + 1, antk);
		}

		// save the route of the ant in the path
		paths[i] = antk.getTabu();

		this->pheromoneUpdateLocal(paths[i], antk);
		this->srvA.getAllAnt()[i].setPosition(paths[i].back());
		antk.clearTabu();
		this->srvA.updateAnt(i + 1, antk);
	}
}

int ACO::edgeSelection(Ant antk)
{
	vector<double> probability;
	probability.resize(this->graph.get_N_node());

	Node src = this->graph.get_node(antk.getPosition());
	for (auto& node : this->graph.getNeighbours(src)) {
		if (antk.visited(node.id) == false) {
			Edge E = this->graph.get_edge(src, node);
			double Trail_Level = pow(E.trailPheromone, this->getAlpha());
			double Atractivness = pow(1 / (double)E.distance, this->getBetha());
			double sum = 0;
			for (auto& nodeDest : this->graph.getNeighbours(src)) {
				if (node.id != nodeDest.id) {
					Edge e = this->graph.get_edge(src, nodeDest);
					double trail_level = pow(e.trailPheromone, this->getAlpha());
					double atractivness = pow(1 / (double)e.distance, this->getBetha());
					sum += trail_level * atractivness;
				}
			}
			probability[node.id] = (Trail_Level * Atractivness) / (double)sum;
		}
	}


	double max = 0;
	int id = 0;
	// generates a new seed for the random number
	for (int i = 0; i < this->graph.get_N_node(); i++) {
		if (max < probability[i]) {
			max = probability[i];
			id = i;
		}
		double random = (double)rand() / RAND_MAX;
		// if edge probability is higher than random then max is replaced by the probability, even if it is < max
		if (probability[i] > random && probability[i] != 0.0) {
			max = probability[i];
			id = i;
		}
	}
	return id;
}

void ACO::pheromoneUpdateLocal(vector<int> path, Ant antk)
{
	int distance = this->getPathDistance(path);
	for (int i = 0; i < path.size() - 1; i++) {
		Edge e = this->graph.get_edge(this->graph.get_node(i), this->graph.get_node(i + 1));
		e.trailPheromone = e.trailPheromone + ((antk.getPheromone() + this->getQ()) / (double)distance);
	}
}

void ACO::pheromoneUpdateGlobal()
{
	for (auto& edge : this->graph.Edges) {
		edge.trailPheromone = (1 - this->getRho()) * edge.trailPheromone;
	}
}

int ACO::bestRoute(vector<vector<int>> paths)
{
	int min = this->getPathDistance(paths[0]);
	int id = 0;
	for (int i = 0; i < paths.size(); i++) {
		if (min > this->getPathDistance(paths[i])) {
			min = this->getPathDistance(paths[i]);
			id = i;
		}
	}
	return id;
}

int ACO::getPathDistance(vector<int> path)
{
	int sum = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		Edge e = this->graph.get_edge(this->graph.get_node(path[i]), this->graph.get_node(path[i + 1]));
		sum += e.distance;
	}
	return sum;
}

void ACO::clearPath(vector<vector<int>>& paths)
{
	for (int i = 0; i < this->srvA.getSizeAnt(); i++) {
		paths[i].clear();
	}
}

void ACO::printPath(vector<int> path)
{
	cout << this->getPathDistance(path) << ":" << path[0];
	for (int i = 1; i < path.size(); i++) {
		cout << " --> " << path[i];
	}
	cout << endl;
}

void ACO::printGraph()
{
	for (int i = 0; i < this->graph.N; i++) {
		cout << i << " --> ";
		for (int j = 0; j < this->graph.adjList[i].size(); j++) {
			Edge e = this->graph.get_edge(this->graph.get_node(i), this->graph.adjList[i][j]);
			cout << this->graph.adjList[i][j].id << ":" << e.distance << ":" << e.trailPheromone << "	";
		}
		cout << endl;
	}
}

void ACO::loadGraph()
{
	this->graph.load_from_file_nodes();
	this->graph.load_from_file_edges();
}

void ACO::setACO(int iterations, int alpha, int betha, double rho, int Q)
{
	this->setIterations(iterations);
	this->setAlpha(alpha);
	this->setBetha(betha);
	this->setRho(rho);
	this->setQ(Q);
}


