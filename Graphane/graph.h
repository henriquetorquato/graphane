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
	bool ContainsNodeLabel(std::string label);
	bool ContainsEdge(Edge edge);

public:
	void AddNode(Node node);
	void AddNodes(std::vector<Node> nodes);
	Node GetNode(std::string label);
	Node* GetNodeAt(int index);
	std::vector<Node> GetNodes() { return nodes; }
	std::vector<std::string> GetNodeLabels();
	int FindNode(std::string label);

	void AddEdge(Edge edge);
	std::vector<Edge> GetEdges() { return edges; }
	std::vector<Edge> GetEdges(std::string node_label);
};