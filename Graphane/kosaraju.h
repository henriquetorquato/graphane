#pragma once
#include "graph.h"

using namespace std;

class Kosaraju
{
private:
	Graph _graph;

public:
	Kosaraju(Graph graph)
	{
		_graph = graph;
	}

	vector<vector<string>> FindStronglyConnectedComponents();
};