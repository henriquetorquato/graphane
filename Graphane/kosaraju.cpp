#include "kosaraju.h"
#include "graph_builder.h"
#include <stack>

map<string, bool> createVisitedNodesMap(vector<string> nodes)
{
	map<string, bool> visited_nodes;
	vector<string>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		visited_nodes.insert(make_pair(*node_i, false));
	}

	return visited_nodes;
}

void resetVisitedNodesMap(map<string, bool> &visited_nodes)
{
	map<string, bool>::iterator it;
	for (it = visited_nodes.begin(); it != visited_nodes.end(); it++)
	{
		it->second = false;
	}
}

Graph createTransposedGraph(Graph original_graph)
{
	GraphBuilder builder;

	builder.AddNodes(original_graph.GetNodeLabels());

	vector<Edge>::iterator edge_i;
	vector<Edge> edges = original_graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge(*edge_i);

		// Create inverse edge
		builder.AddEdge(
			edge.GetLabel(),
			edge.GetValue(),
			edge.GetNodeB(),
			edge.GetNodeA(),
			edge.GetType()
		);
	}

	return builder.Build();
}

void DepthFirstSearch(string node, Graph graph, map<string, bool>& visited_nodes, vector<string>& path, stack<string>& node_stack)
{
	// Mark node as visited
	visited_nodes[node] = true;

	/*
	* Add node to component.
	* Only used when calculating the components (second use of DFS).
	*/ 
	path.push_back(node);

	vector<string>::iterator neighbour_i;
	vector<string> neighbours = graph.GetNeighbours(node);

	// Traverse graph
	for (neighbour_i = neighbours.begin(); neighbour_i != neighbours.end(); neighbour_i++)
	{
		string neighbour = *neighbour_i;
		if (visited_nodes[neighbour])
		{
			continue;
		}

		DepthFirstSearch(neighbour, graph, visited_nodes, path, node_stack);
	}

	node_stack.push(node);
}

vector<vector<string>> Kosaraju::FindStronglyConnectedComponents()
{
	vector<vector<string>> components;

	stack<string> node_stack;

	vector<string> nodes = _graph.GetNodeLabels();
	map<string, bool> visited_nodes = createVisitedNodesMap(nodes);

	vector<string>::iterator node_i;
	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++)
	{
		string node = *node_i;
		if (visited_nodes[node])
		{
			continue;
		}

		vector<string> path;
		DepthFirstSearch(node, _graph, visited_nodes, path, node_stack);
	}

	Graph transposed_graph = createTransposedGraph(_graph);
	resetVisitedNodesMap(visited_nodes);

	do
	{
		string node = node_stack.top();
		node_stack.pop();

		if (visited_nodes[node])
		{
			continue;
		}

		vector<string> component;
		stack<string> mock_stack;
		DepthFirstSearch(node, transposed_graph, visited_nodes, component, mock_stack);

		components.push_back(component);
	} while (!node_stack.empty());

	return components;
}