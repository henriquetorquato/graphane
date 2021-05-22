#include "graph_builder.h"
#include <stdexcept>
#include <map>

void GraphBuilder::AddNode(string label)
{
	Node node(label);

	if (FindNode(node).has_value())
	{
		throw runtime_error("Node already exists.");
		return;
	}

	_nodes.push_back(node);
}

void GraphBuilder::AddNodes(vector<string> labels)
{
	vector<string>::iterator label_i;

	for (label_i = labels.begin(); label_i != labels.end(); label_i++)
	{
		AddNode(*label_i);
	}
}

void GraphBuilder::AddEdge(string label, int value, string node_a, string node_b, EdgeType type)
{
	Edge edge(label, value, node_a, node_b, type);

	// If the edge already exists, it should be bidirectional
	if (optional<int> found_index = FindEdge(edge))
	{
		_edges.at(found_index.value()).SetType(EdgeType::Bidirectional);
		return;
	}

	if (ContainsEdgeLabel(edge.GetLabel()))
	{
		throw runtime_error("Edge label already exists.");
		return;
	}

	if (!ContainsNodeLabel(edge.GetNodeA()))
	{
		throw runtime_error("Node A was not found");
		return;
	}

	if (!ContainsNodeLabel(edge.GetNodeB()))
	{
		throw runtime_error("Node B was not found");
		return;
	}

	_edges.push_back(edge);
}

Graph GraphBuilder::Build()
{
	return Graph(_nodes, _edges);
}

optional<int> GraphBuilder::FindNode(Node node)
{
	vector<Node>::iterator node_i;

	for (node_i = _nodes.begin(); node_i != _nodes.end(); node_i++)
	{
		Node current_node = *node_i;
		if (current_node.GetLabel() == node.GetLabel())
		{
			return distance(_nodes.begin(), node_i);
		}
	}

	return nullopt;
}

optional<int> GraphBuilder::FindEdge(Edge edge)
{
	vector<Edge>::iterator edge_i;

	for (edge_i = _edges.begin(); edge_i != _edges.end(); edge_i++)
	{
		Edge current_edge = *edge_i;

		// If they share same nodes
		if (current_edge.SignatureMatch(edge))
		{
			return distance(_edges.begin(), edge_i);
		}
	}

	return nullopt;
}

bool GraphBuilder::ContainsNodeLabel(string label)
{
	vector<Node>::iterator node_i;
	for (node_i = _nodes.begin(); node_i != _nodes.end(); node_i++)
	{
		string current_label = (*node_i).GetLabel();
		if (current_label == label)
		{
			return true;
		}
	}

	return false;
}

bool GraphBuilder::ContainsEdgeLabel(string label)
{
	vector<Edge>::iterator edge_i;
	for (edge_i = _edges.begin(); edge_i != _edges.end(); edge_i++)
	{
		string current_label = (*edge_i).GetLabel();
		if (current_label == label)
		{
			return true;
		}
	}

	return false;
}