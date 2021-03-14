#pragma once
#include "string"

class Node
{
private:
	std::string m_label;

public:
	Node(std::string label)
	{
		m_label = label;
	}

	bool operator == (const Node& node_ref) const
	{
		return node_ref.m_label == m_label;
	}

	std::string GetLabel() { return m_label; }
};