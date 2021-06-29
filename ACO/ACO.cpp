#include <iostream>
#include <vector>
#include <time.h>
#include "Test.h"
#include "Graph.h"
#include "FileRepository.h"
#include "ServiceAnt.h"
#include "AntColonyOptimization.h"
#include "UI.h"

int main()
{
    srand(unsigned(time(NULL)));
    test_ant();
    test_graph();
    test_repo();
    test_service_ant();
    test_ACO();

    vector<Node> nodes;
    vector<Edge> edges;
    Graph graph(nodes, edges, "nodes.txt", "edges.txt");
    RepoFile repoA("ants.txt");
    repoA.load_from_file();
    ServiceAnt srvA(repoA);
    ACO aco(graph, srvA, 50, 1, 1, 0.1, 1);
    UserInterface ui(srvA, aco);


    ui.runConsole();

}
