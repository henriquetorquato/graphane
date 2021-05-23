#pragma once
#include "graph.h"
#include "ford_fulkerson_result.h"

class FordFulkerson
{
private:
	Graph _graph;

	static bool IsSourceValid(Graph graph, string source);
	static bool IsTerminalValid(Graph graph, string terminal);

public:
	FordFulkerson(Graph graph)
	{
		_graph = graph;
	}

	static bool IsGraphValid(Graph graph, string source, string terminal);
	int FindMaximumFlow(string source, string terminal);
};