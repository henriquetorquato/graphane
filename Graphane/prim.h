#pragma once
#include "graph.h"
#include "prim_result.h"
#include <time.h>

class Prim 
{
private:
	Graph m_graph;
	void SeedRand(int seed)
	{
		int seed_numer = seed == NULL
			// If no seed is provided, used random seed
			? (int)time(NULL)
			: seed;

		// Seed random number generator "rand()"
		srand(seed_numer);
	};

public:
	Prim(Graph graph, int seed = NULL)
	{
		m_graph = graph;
		SeedRand(seed);
	}

	vector<PrimResult> FindMinimumSpanningTree();
};
