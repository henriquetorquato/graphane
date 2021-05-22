#pragma once
#include "graph.h"
#include "dijkstra_result.h"

using namespace std;

class Dijkstra
{
private:
	Graph _graph;

public:
	Dijkstra(Graph graph)
	{
		_graph = graph;
	}

	vector<DijkstraResult> FindShortestPath(string origin_label, string destination_label = string());
};