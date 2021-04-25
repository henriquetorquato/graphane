#pragma once
#include "string"
#include "node.h"
#include <vector>

using namespace std;

class Edge
{
private:
	int m_value;
	string m_label;
	Node* m_node_a;
	Node* m_node_b;

public:
	Edge(string label, int value, Node* node_a, Node* node_b)
	{
		m_label = label;
		m_value = value;
		m_node_a = node_a;
		m_node_b = node_b;
	}

	bool operator == (const Edge& edge_ref) const
	{
		return (edge_ref.m_node_a == m_node_a || edge_ref.m_node_a == m_node_b)
			&& (edge_ref.m_node_b == m_node_a || edge_ref.m_node_b == m_node_b);
	}

	string GetLabel() { return m_label; }
	int GetValue() { return m_value; }
	Node* GetNodeA() { return m_node_a; }
	Node* GetNodeB() { return m_node_b; }

	bool ContainsNode(string label);
	Node* GetNodeNeighbour(string label);

	bool SignatureMatch(Edge edge);
};