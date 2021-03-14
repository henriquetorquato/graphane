#pragma once
#include <vector>
#include "node.h"
#include "edge.h"

class Graph
{
private:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	bool ContainsNode(Node node);

public:
	void AddNode(Node node);
	void AddEdge(Edge edge);
};