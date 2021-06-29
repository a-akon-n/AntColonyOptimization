#include "Test.h"
#include "Ant.h"
#include "MyException.h"
#include "ValidatorAnt.h"
#include "Graph.h"
#include "FileRepository.h"
#include "ServiceAnt.h"
#include "AntColonyOptimization.h"
#include <cassert>
#include <iostream>
#include <time.h>

using namespace std;


void test_ant()
{
	Ant a1;
	assert(a1.getID() == 0);
	assert(a1.getStart() == 0);
	assert(a1.getPosition() == 0);
	assert(a1.getPheromone() == 0.0);
	assert(a1.getTabu().size() == 0);

	Ant a2(1, 0, 0, 1.2, { 0,5 });

	assert(a2.getID() == 1);
	assert(a2.getStart() == 0);
	assert(a2.getPosition() == 0);
	assert(a2.getPheromone() == 1.2);
	assert(a2.getTabu().size() == 2);
	assert(a2.getTabu()[0] == 0);
	assert(a2.getTabu()[1] == 5);

	a1 = a2;

	assert(a1.getID() == 1);
	assert(a1.getStart() == 0);
	assert(a1.getPosition() == 0);
	assert(a1.getPheromone() == 1.2);
	assert(a1.getTabu().size() == 2);
	assert(a1.getTabu()[0] == 0);
	assert(a1.getTabu()[1] == 5);

	assert(a1 == a2);
}

void test_graph()
{
	Node n = { 0 };
	Node n1 = { 1 };
	Node n2 = { 2 };
	Node n3 = { 3 };
	Node n4 = { 4 };
	Node n5 = { 5 };
	vector<Node> nodes = { n,n1,n2,n3,n4 };
	vector<Edge> edges = {
		{n,n1,5},
		{n,n4,6},
		{n1,n2,5},
		{n1,n3,7},
		{n2,n3,3},
		{n3,n4,13},
		{n4,n1,10},
	};
	Graph g1;
	assert(g1.get_N_node() == 0);
	assert(g1.get_N_edge() == 0);
	for (int i = 0; i < nodes.size(); i++) {
		g1.addNode(nodes[i]);
	}
	assert(g1.get_N_node() == 5);
	for (int i = 0; i < edges.size(); i++) {
		g1.addEdge(edges[i]);
	}
	assert(g1.get_N_edge() == 7);

	Graph g2(nodes, edges, "node_test.txt", "edge_test.txt");
	Edge e = { n1, n5, 7 };

	g2.addNode(n5);
	g2.addEdge(e);

	assert(g2.get_N_node() == 6);
	assert(g2.get_N_edge() == 8);

	assert(g2.getNeighbours(n5)[0].id == n1.id);

	assert(g2.get_edge(n, n4).src.id == edges[1].src.id);

}

void test_repo()
{
	RepoFile repo;

	Ant a1(1, 0, 0, 1.2, { 0,5 });
	Ant a2(2, 0, 0, 1.5, { 0,2,4,5 });
	Ant a3(3, 0, 0, 1.5, { 0 });


	assert(repo.getDimRepo() == 0);
	repo.addElem(a1);
	assert(repo.getDimRepo() == 1);
	assert(repo.getElem(1).getID() == a1.getID());
	assert(repo.getAll()[0] == a1);

	repo.updateElem(a2, a1);
	assert(repo.getElem(1) == a2);
	assert(repo.getAll()[0] == a2);

	repo.deleteElem(a2);
	assert(repo.getDimRepo() == 0);

	Repo repo2({ a1,a2,a3 });
	assert(repo2.getDimRepo() == 3);
}

void test_service_ant()
{
	RepoFile repoA("ant_test.txt");
	ServiceAnt srvA(repoA);
	srvA.loadAnt();
	assert(srvA.getSizeAnt() == 9);

	srvA.addAnt(10, 0, 0, 0.1, {});
	assert(srvA.getSizeAnt() == 10);
	assert(srvA.getAllAnt().size() == 10);

	Ant a(10, 1, 1, 0.2, {});

	assert(srvA.getAnt(10).getID() == 10);
	assert(srvA.getAnt(10).getStart() == 0);
	assert(srvA.getAnt(10).getPosition() == 0);
	assert(srvA.getAnt(10).getPheromone() == 0.1);

	srvA.updateAnt(10, a);

	assert(srvA.getAnt(10).getID() == 10);
	assert(srvA.getAnt(10).getStart() == 1);
	assert(srvA.getAnt(10).getPosition() == 1);
	assert(srvA.getAnt(10).getPheromone() == 0.2);

	srvA.deleteAnt(10);
	assert(srvA.getSizeAnt() == 9);
	assert(srvA.getAllAnt().size() == 9);
}

void test_ACO()
{
	srand((unsigned)time(NULL));
	Ant a1(1, 3, 3, 0.333, {});
	Ant a2(2, 0, 0, 0.1, {});
	Ant a3(3, 7, 7, 0.12, {});
	Ant a4(4, 3, 3, 0.662, {});
	Ant a5(5, 8, 8, 0.76, {});
	Ant a6(6, 5, 5, 0.22, {});
	Ant a7(7, 6, 6, 0.65, {});
	Ant a8(8, 4, 4, 0.143, {});
	Ant a9(9, 2, 2, 0.2432, {});

	Node n = { 0, };
	Node n1 = { 1, };
	Node n2 = { 2, };
	Node n3 = { 3, };
	Node n4 = { 4, };
	Node n5 = { 5, };
	Node n6 = { 6, };
	Node n7 = { 7, };
	Node n8 = { 8, };
	vector<Node> nodes = { n,n1,n2,n3,n4,n5,n6,n7,n8 };
	vector<Edge> edges = {
		{n,n1,5},
		{n,n2,2},
		{n,n3,5},
		{n,n4,14},
		{n,n5,5},
		{n,n6,3},
		{n,n7,10},
		{n,n8,5},
		{n1,n2,10},
		{n1,n3,8},
		{n1,n4,5},
		{n1,n5,22},
		{n1,n6,4},
		{n1,n7,7},
		{n1,n8,20},
		{n2,n3,5},
		{n2,n4,12},
		{n2,n5,8},
		{n2,n6,11},
		{n2,n7,4},
		{n2,n8,13},
		{n3,n4,3},
		{n3,n5,1},
		{n3,n6,4},
		{n3,n7,22},
		{n3,n8,5},
		{n4,n5,10},
		{n4,n6,7},
		{n4,n7,9},
		{n4,n8,42},
		{n5,n6,4},
		{n5,n7,22},
		{n5,n8,6},
		{n6,n7,1},
		{n6,n8,12},
		{n7,n8,11}
	};

	RepoFile repo("ant_test.txt");
	ServiceAnt srvA(repo);
	srvA.loadAnt();
	Graph graph(nodes, edges, "test_node.txt", "test_edge.txt");
	ACO aco(graph, srvA, 100, 5, 1, 0.1, 10);

	a1.addTabu(0);
	a1.addTabu(1);
	a1.addTabu(2);
	a1.addTabu(3);
	a1.addTabu(4);
	a1.addTabu(5);
	a1.addTabu(6);
	a1.addTabu(7);
	assert(aco.edgeSelection(a1) == 8);

	a1.clearTabu();
	a1.addTabu(0);
	a1.addTabu(1);
	a1.addTabu(3);
	a1.addTabu(4);
	a1.addTabu(5);
	a1.addTabu(6);
	a1.addTabu(7);
	a1.addTabu(8);
	assert(aco.edgeSelection(a1) == 2);





	cout << "Passed tests 5" << endl;
}
