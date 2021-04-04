#include "graph.h"
#include <stdexcept>

void Graph::AddNode(Node node)
{
	if (ContainsNode(node))
	{
		throw std::runtime_error("Node already exists.");
		return;
	}

	nodes.push_back(node);
}

void Graph::AddNodes(std::vector<Node> nodes)
{
	std::vector<Node>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		AddNode(*node_i);
	}
}

Node Graph::GetNode(std::string label)
{
	int index(FindNode(label));
	if (index == -1)
	{
		throw std::runtime_error("Node not found");
	}

	return nodes.at(index);
}

Node* Graph::GetNodeAt(int index)
{
	return &nodes.at(index);
}

std::vector<std::string> Graph::GetNodeLabels()
{
	std::vector<std::string> result;
	std::vector<Node>::iterator node_i;

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
		throw std::runtime_error("Node A was not found");
		return;
	}

	if (!ContainsNodeLabel(edge.GetNodeB()->GetLabel()))
	{
		throw std::runtime_error("Node B was not found");
		return;
	}

	edges.push_back(edge);
}

std::vector<Edge> Graph::GetEdges(std::string node_label)
{
	std::vector<Edge> result;
	std::vector<Edge>::iterator edge_i;

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

int Graph::FindNode(std::string label)
{
	int index = 0;
	std::vector<Node>::iterator node_i;

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
	return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
}

bool Graph::ContainsNodeLabel(std::string label)
{
	std::vector<Node>::iterator node_i;
	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		std::string current_label = (*node_i).GetLabel();
		if (current_label == label)
		{
			return true;
		}
	}

	return false;
}

bool Graph::ContainsEdge(Edge edge)
{
	return std::find(edges.begin(), edges.end(), edge) != edges.end();
}