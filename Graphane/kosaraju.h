#pragma once
#include "graph.h"

using namespace std;

struct KosarajuComponents
{
	vector<string> nodes;
};

struct KosarajuResult
{
	vector<KosarajuComponents> components;
};

class Kosaraju
{
private:
	Graph _graph;

public:
	Kosaraju(Graph graph)
	{
		_graph = graph;
	}

	void DisplayResult(KosarajuResult result);
	KosarajuResult FindStronglyConnectedComponents();
};