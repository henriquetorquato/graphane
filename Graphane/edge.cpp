#include "edge.h"

bool Edge::ContainsNode(std::string label)
{
	return m_node_a->GetLabel() == label
		|| m_node_b->GetLabel() == label;
}

Node* Edge::GetNodeNeighbour(std::string label)
{
	return m_node_a->GetLabel() == label
		? m_node_b
		: m_node_a;
}