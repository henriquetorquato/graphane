#include "graph.h"
#include <stdexcept>

using namespace std;

void Graph::AddNode(Node node)
{
	if (ContainsNode(node))
	{
		throw runtime_error("Node already exists.");
		return;
	}

	nodes.push_back(node);
}

void Graph::AddEdge(Edge edge)
{
	// If the edge already exists, it should be bidirectional
	if (optional<int> found_index = FindEdge(edge))
	{
		GetEdgeAt(found_index.value())->SetType(EdgeType::Bidirectional);
		return;
	}

	if (ContainsEdgeLabel(edge.GetLabel()))
	{
		throw runtime_error("Edge label already exists.");
		return;
	}

	if (!ContainsNodeLabel(edge.GetNodeA()->GetLabel()))
	{
		throw runtime_error("Node A was not found");
		return;
	}

	if (!ContainsNodeLabel(edge.GetNodeB()->GetLabel()))
	{
		throw runtime_error("Node B was not found");
		return;
	}

	edges.push_back(edge);
}

void Graph::AddNodes(vector<Node> nodes)
{
	vector<Node>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		AddNode(*node_i);
	}
}

void Graph::AddEdges(vector<Edge> edges)
{
	vector<Edge>::iterator edge_i;

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		AddEdge(*edge_i);
	}
}

Node Graph::GetNode(string label)
{
	optional<int> node_index(FindNode(label));
	if (!node_index)
	{
		throw runtime_error("Node not found");
	}

	return nodes.at(node_index.value());
}

vector<string> Graph::GetNodeLabels()
{
	vector<string> result;
	vector<Node>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		Node node = *node_i;
		result.push_back(node.GetLabel());
	}

	return result;
}

Node* Graph::GetNodeAt(int index)
{
	return &nodes.at(index);
}

Edge* Graph::GetEdgeAt(int index)
{
	return &edges.at(index);
}

vector<Edge> Graph::GetEdges(string node_label)
{
	vector<Edge> result;
	vector<Edge>::iterator edge_i;

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge = *edge_i;
		if (edge.ContainsNode(node_label))
		{
			result.push_back(edge);
		}
	}

	return result;
}

optional<int> Graph::FindNode(Node node)
{
	vector<Node>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		Node current_node = *node_i;
		if (current_node.GetLabel() == node.GetLabel())
		{
			return distance(nodes.begin(), node_i);
		}
	}

	return nullopt;
}

optional<int> Graph::FindEdge(Edge edge)
{
	vector<Edge>::iterator edge_i;

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge current_edge = *edge_i;

		// If they share same nodes
		if (current_edge.SignatureMatch(edge))
		{
			return distance(edges.begin(), edge_i);
		}
	}

	return nullopt;
}

bool Graph::ContainsNode(Node node)
{
	return find(nodes.begin(), nodes.end(), node) != nodes.end();
}

bool Graph::ContainsNodeLabel(string label)
{
	vector<Node>::iterator node_i;
	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		string current_label = (*node_i).GetLabel();
		if (current_label == label)
		{
			return true;
		}
	}

	return false;
}

bool Graph::ContainsEdgeLabel(string label)
{
	vector<Edge>::iterator edge_i;
	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		string current_label = (*edge_i).GetLabel();
		if (current_label == label)
		{
			return true;
		}
	}

	return false;
}