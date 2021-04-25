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
	int index(FindNode(label));
	if (index == -1)
	{
		throw runtime_error("Node not found");
	}

	return nodes.at(index);
}

Node* Graph::GetNodeAt(int index)
{
	return &nodes.at(index);
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

void Graph::AddEdge(Edge edge)
{
	if (ContainsEdge(edge))
	{
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

int Graph::FindNode(string label)
{
	int index = 0;
	vector<Node>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		Node node = *node_i;
		if (node.GetLabel() == label)
		{
			return index;
		}

		index++;
	}

	return -1;
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

bool Graph::ContainsEdge(Edge edge)
{
	vector<Edge>::iterator edge_i;

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge current_edge = *edge_i;

		// If they share same nodes or have the same label
		if (current_edge.SignatureMatch(edge) || current_edge.GetLabel() == edge.GetLabel())
		{
			return true;
		}
	}

	return false;
}