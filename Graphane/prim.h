#pragma once
#include "graph.h"

class Prim 
{
private:
	Graph m_graph;

public:
	Prim(Graph graph)
	{
		m_graph = graph;
	}

	void FindMinimumSpanningTree();
};
