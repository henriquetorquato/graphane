#include "graph_utils.h"

using namespace std;

bool IsNonDirectional(Graph graph)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge(*edge_i);

		/*
		* If there is any directional edges,
		* then the graph is directional.
		*/
		if (edge.IsDirectional())
		{
			return false;
		}
	}

	return true;
}

bool IsFullyDirectional(Graph graph)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge(*edge_i);

		/*
		* If there is any bi-directional edge,
		* then the graph is not fully directional.
		*/
		if (edge.IsBidirectional())
		{
			return false;
		}
	}

	return true;
}