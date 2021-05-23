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
	int _value;
	string _label;
	string _node_a;
	string _node_b;
	EdgeType _type;

public:
	Edge(string label, int value, string node_a, string node_b, EdgeType type)
	{
		_label = label;
		_value = value;
		_node_a = node_a;
		_node_b = node_b;
		_type = type;
	}

	Edge(string label, int value, string node_a, string node_b)
		: Edge(label, value, node_a, node_b, EdgeType::Directional) {}

	bool operator == (const Edge& edge_ref) const
	{
		return edge_ref._label == _label
			&& edge_ref._value == _value
			&& edge_ref._node_a == _node_a
			&& edge_ref._node_b == _node_b
			&& edge_ref._type == _type;
	}

	int GetValue() { return _value; }
	string GetLabel() { return _label; }
	
	string GetNodeA() { return _node_a; }
	string GetNodeB() { return _node_b; }

	bool IsBidirectional()
	{
		return _type == EdgeType::Bidirectional;
	}

	bool IsDirectional()
	{
		return _type == EdgeType::Directional;
	}

	void SetType(EdgeType type)
	{ 
		_type = type;
	}

	bool ContainsNode(string label);
	bool SignatureMatch(Edge edge);
	string GetNeighbour(string label);
};