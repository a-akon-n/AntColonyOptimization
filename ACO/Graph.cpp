#include "Graph.h"
#include <iostream>
#include <fstream>

Graph::Graph()
{
	this->N = 0;
	this->adjList.resize(this->N);
	this->Nodes.resize(this->N);
	this->Edges.resize(this->N);
	this->filenameN = "";
	this->filenameE = "";
}

Graph::Graph(const Graph& g)
{
	this->adjList.reserve(g.adjList.size());
	this->adjList = g.adjList;
	this->Nodes.reserve(g.Nodes.size());
	this->Nodes = g.Nodes;
	this->Edges.reserve(g.Nodes.size());
	this->Edges = g.Edges;
	this->N = g.N;
	this->filenameN = g.filenameN;
	this->filenameE = g.filenameE;
}

Graph::Graph(const vector<Node>& nodes, const vector<Edge>& edges, string filenameN, string filenameE)
{
	this->N = nodes.size();
	this->Nodes.resize(nodes.size());
	this->Nodes = nodes;
	this->Edges.resize(edges.size());
	this->Edges = edges;
	this->adjList.resize(this->N);
	for (auto& edge : this->Edges) {
		this->adjList[edge.src.id].push_back(edge.dest);
		this->adjList[edge.dest.id].push_back(edge.src);
	}
	this->filenameN = filenameN;
	this->filenameE = filenameE;
}

Graph::~Graph()
{
	this->N = 0;
	this->Nodes.clear();
	this->Nodes.resize(this->N);
	this->Edges.clear();
	this->Edges.resize(this->N);
	this->adjList.clear();
	this->adjList.resize(this->N);
	this->filenameN = "";
	this->filenameE = "";
}

int Graph::get_N_node()
{
	return this->N;
}


int Graph::get_N_edge()
{
	return this->Edges.size();
}

Node Graph::get_node(int id)
{
	return this->Nodes[id];
}

Edge Graph::get_edge(Node src, Node dest)
{
	for (int i = 0; i < this->Edges.size(); i++) {
		if (this->Edges[i].src.id == src.id && this->Edges[i].dest.id == dest.id)
			return this->Edges[i];
		else if (this->Edges[i].src.id == dest.id && this->Edges[i].dest.id == src.id)
			return this->Edges[i];
	}
}

void Graph::addEdge(const Edge& e)
{
	this->Edges.push_back(e);
	adjList.resize(this->N);
	adjList[e.src.id].push_back(e.dest);
	adjList[e.dest.id].push_back(e.src);
	this->save_to_file_edges();
}

void Graph::addNode(const Node& node)
{
	this->Nodes.push_back(node);
	this->N = this->Nodes.size();
	this->save_to_file_nodes();
}

void Graph::deleteNode(Node n)
{
	for (int i = 0; i < this->Nodes.size(); i++) {
		if (this->Nodes[i].id == n.id) {
			for (int j = i; j < this->Nodes.size() - 1; j++) {
				this->Nodes[j] = this->Nodes[j + 1];
			}
			this->Nodes.pop_back();
		}
	}
	this->save_to_file_nodes();
}

vector<Node> Graph::getNeighbours(Node n)
{
	return this->adjList[n.id];
}

Graph& Graph::operator=(const Graph& graph)
{
	this->N = graph.N;
	this->adjList.clear();
	this->adjList.resize(graph.adjList.size());
	this->adjList = graph.adjList;
	this->Nodes.clear();
	this->Nodes.resize(graph.Nodes.size());
	this->Nodes = graph.Nodes;
	this->Edges.clear();
	this->Edges.resize(graph.Edges.size());
	this->Edges = graph.Edges;
	this->filenameN = graph.filenameN;
	this->filenameE = graph.filenameE;
	return *this;
}

void Graph::load_from_file_nodes()
{
	ifstream in(this->filenameN);
	int nr;
	in >> nr;

	for (int i = 0; i < nr; i++) {
		int id;
		in >> id;
		Node n;
		n.id = id;
		this->addNode(n);
	}
	in.close();
}

void Graph::save_to_file_nodes()
{
	ofstream out(this->filenameN);

	out << this->get_N_node() << endl;

	for (int i = 0; i < this->get_N_node(); i++) {
		out << i << endl;
	}
	out.close();
}

void Graph::load_from_file_edges()
{
	ifstream in(this->filenameE);
	while (true) {
		Node src, dest;
		int id, distance;
		in >> id;
		if (in.eof())break;
		src = this->get_node(id);
		in >> id;
		dest = this->get_node(id);
		in >> distance;
		Edge e;
		e.src = src;
		e.dest = dest;
		e.distance = distance;
		this->addEdge(e);
	}
	in.close();
}

void Graph::save_to_file_edges()
{
	ofstream out(this->filenameE);

	for (int i = 0; i < this->get_N_edge(); i++) {
		out << this->Edges[i].src.id << endl << this->Edges[i].dest.id << endl << this->Edges[i].distance << endl;
	}
	out.close();
}
