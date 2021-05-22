#include "edge.h"
#include <stdexcept>

using namespace std;

bool Edge::ContainsNode(string label)
{
	return _node_a == label || _node_b == label;
}

bool Edge::SignatureMatch(Edge edge)
{
	// If container both edge nodes
	return ContainsNode(edge.GetNodeA()) && ContainsNode(edge.GetNodeB());
}

bool Edge::IsBidirectional()
{
	return _type == EdgeType::Bidirectional;
}

string Edge::GetNeighbour(string label)
{
	string neighbor = _node_a == label ? _node_b
		: _node_b == label ? _node_a
		: string();

	if (neighbor == string())
	{
		throw runtime_error("Node " + label + " was not found");
	}

	return neighbor;
}