#pragma once
#include "graph.h"

using namespace std;

struct ShortestPath
{
	string origin;
	string destination;
	vector<string> path;
	int weight;
};

struct DijkstraResult
{
	vector<ShortestPath> paths;
};

class Dijkstra
{
private:
	Graph _graph;

public:
	Dijkstra(Graph graph)
	{
		_graph = graph;
	}

	void DisplayResult(DijkstraResult result);
	DijkstraResult FindShortestPath(string origin_label, string destination_label = string());
};