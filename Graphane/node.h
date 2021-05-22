#pragma once
#include "string"

class Node
{
private:
	std::string _label;

public:
	Node(std::string label)
	{
		_label = label;
	}

	bool operator == (const Node& node_ref) const
	{
		return node_ref._label == _label;
	}

	std::string GetLabel() { return _label; }
};