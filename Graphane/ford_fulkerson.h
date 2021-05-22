#pragma once
#include "graph.h"
#include "ford_fulkerson_result.h"

class FordFulkerson
{
private:
	Graph _graph;

public:
	FordFulkerson(Graph graph)
	{
		_graph = graph;
	}

	vector<FordFulkersonResult> FindMaximumFlow(string source, string terminal);
};