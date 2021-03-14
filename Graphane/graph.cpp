#include "graph.h"
#include <stdexcept>

void Graph::AddNode(Node node)
{
	if (ContainsNode(node))
	{
		throw std::runtime_error("Node already exists.");
		return;
	}

	nodes.push_back(node);
}

void Graph::AddEdge(Edge edge)
{
	std::vector<Node> nodes = edge.GetNodes();

	for (Node node : nodes)
	{
		if (!ContainsNode(node))
		{
			throw std::runtime_error("Edge node not found on graph");
			return;
		}
	}

	edges.push_back(edge);
}

bool Graph::ContainsNode(Node node)
{
	return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
}
