#pragma once
#include "graph.h"

class Dijkstra
{
private:
	Graph m_graph;

public:
	Dijkstra(Graph graph)
	{
		m_graph = graph;
	}

	void FindShortestPath(std::string origin_label);
};