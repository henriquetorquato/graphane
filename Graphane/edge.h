#pragma once
#include "string"
#include "node.h"
#include <vector>

class Edge
{
private:
	std::string m_label;
	std::vector<Node> nodes;

public:
	Edge(std::string label)
	{
		m_label = label;
	}

	std::string GetLabel() { return m_label; }
	void AddNode(Node node) { nodes.push_back(node); }
	std::vector<Node> GetNodes() { return nodes; }
};