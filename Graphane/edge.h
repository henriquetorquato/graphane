#pragma once
#include "string"
#include "node.h"
#include <vector>

using namespace std;

enum class EdgeType {
	Directional,
	Bidirectional
};

class Edge
{
private:
	int m_value;
	string m_label;
	Node* m_node_a;
	Node* m_node_b;
	EdgeType m_type;

public:
	Edge(string label, int value, Node* node_a, Node* node_b, EdgeType type)
	{
		m_label = label;
		m_value = value;
		m_node_a = node_a;
		m_node_b = node_b;
		m_type = type;
	}

	Edge(string label, int value, Node* node_a, Node* node_b)
		: Edge(label, value, node_a, node_b, EdgeType::Directional) {}

	string GetLabel() { return m_label; }
	int GetValue() { return m_value; }
	Node* GetNodeA() { return m_node_a; }
	Node* GetNodeB() { return m_node_b; }
	void SetType(EdgeType type) { m_type = type; }

	bool ContainsNode(string label);
	Node* GetNodeNeighbour(string label);

	bool SignatureMatch(Edge edge);
};