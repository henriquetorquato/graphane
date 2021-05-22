#include "ford_fulkerson.h"

vector<FordFulkersonResult> FordFulkerson::FindMaximumFlow(string source, string terminal)
{
	return vector<FordFulkersonResult>();
}

bool FordFulkerson::IsGraphValid(Graph graph, string source, string terminal)
{
	return IsSourceValid(graph, source) && IsTerminalValid(graph, terminal);
}

// The source can't have any edges directed to it
bool FordFulkerson::IsSourceValid(Graph graph, string source)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge = (*edge_i);

		/*
		* If it's a directional edge destination
		* or, if it's part of a bi-directional edge.
		*/
		bool isInvalid = (edge.IsDirectional() && edge.GetNodeB() == source)
			|| (edge.IsBidirectional() && edge.ContainsNode(source));

		if (isInvalid)
		{
			return false;
		}
	}

	return true;
}

// The terminal can't have any edges originating from it
bool FordFulkerson::IsTerminalValid(Graph graph, string terminal)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge = (*edge_i);

		/*
		* If it's a directional edge origin
		* or, if it's part of a bi-directional edge.
		*/
		bool isInvalid = (edge.IsDirectional() && edge.GetNodeA() == terminal)
			|| (edge.IsBidirectional() && edge.ContainsNode(terminal));

		if (isInvalid)
		{
			return false;
		}
	}

	return true;
}