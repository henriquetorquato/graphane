#pragma once
#include "graph.h"
#include <time.h>

using namespace std;

struct PrimPath
{
	string origin;
	string destination;
	string edge;
};

struct PrimResult
{
	vector<PrimPath> paths;
};

class Prim 
{
private:
	Graph _graph;

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
		_graph = graph;
		SeedRand(seed);
	}

	static bool IsGraphValid(Graph graph);

	void DisplayResult(PrimResult result);
	PrimResult FindMinimumSpanningTree();
};