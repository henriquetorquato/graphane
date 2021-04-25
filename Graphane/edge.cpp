#include "edge.h"

using namespace std;

bool Edge::ContainsNode(string label)
{
	return m_node_a->GetLabel() == label
		|| m_node_b->GetLabel() == label;
}

Node* Edge::GetNodeNeighbour(string label)
{
	return m_node_a->GetLabel() == label
		? m_node_b
		: m_node_a;
}

bool Edge::SignatureMatch(Edge edge)
{
	// If container both edge nodes
	return ContainsNode(edge.GetNodeA()->GetLabel())
		&& ContainsNode(edge.GetNodeB()->GetLabel());
}