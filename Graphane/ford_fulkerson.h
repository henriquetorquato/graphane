#pragma once
#include "graph.h"

using namespace std;

struct FordFulkersonResult
{
	int value;
};

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

	void DisplayResult(FordFulkersonResult result);
	FordFulkersonResult FindMaximumFlow(string source, string terminal);
};