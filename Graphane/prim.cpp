#include "prim.h"
#include "string_utils.h"
#include <sstream>
#include <iostream>
#include "graph_utils.h"

struct EdgePath
{
	string label;
	string origin;
	string destination;
	int value;
};

EdgePath CreateEdgePath(Edge edge, string originator)
{
	string neightbour = edge.GetNeighbour(originator);
	return { edge.GetLabel(), originator, neightbour, edge.GetValue() };
}

EdgePath GetClosestEdge(vector<EdgePath> edges)
{
	if (edges.size() == 0)
	{
		return { string(), string(), string(), 0 };
	}

	EdgePath closest_edge = edges.at(0);
	vector<EdgePath>::iterator edges_i;

	for (edges_i = edges.begin() + 1; edges_i != edges.end(); edges_i++)
	{
		EdgePath current_edge = *edges_i;
		if (current_edge.value < closest_edge.value)
		{
			closest_edge = current_edge;
		}
	}

	return closest_edge;
}

bool IsEdgeInVector(vector<EdgePath> edges, Edge edge)
{
	vector<EdgePath>::iterator edges_i;
	for (edges_i = edges.begin(); edges_i != edges.end(); edges_i++)
	{
		EdgePath current = *edges_i;

		if (edge.ContainsNode(current.origin) && edge.ContainsNode(current.destination))
		{
			return true;
		}
	}

	return false;
}

void PopEdge(vector<EdgePath> &edge_pool, string label)
{
	int current_index = 0;
	int edge_index = -1;
	vector<EdgePath>::iterator edge_i;

	for (edge_i = edge_pool.begin(); edge_index == -1 || edge_i != edge_pool.end(); edge_i++, current_index++)
	{
		if ((*edge_i).label == label)
		{
			edge_index = current_index;
		}
	}

	if (edge_index > -1)
	{
		edge_pool.erase(edge_pool.begin() + edge_index);
	}
}

string PopNode(vector<string> &node_pool, string label)
{
	string selected_label;

	int index = label == string()
		? rand() % node_pool.size()
		: FindString(node_pool, label);

	if (index != -1)
	{
		selected_label = node_pool[index];
		node_pool.erase(node_pool.begin() + index);
	}

	return selected_label;
}

void SelectNode(vector<string> &selected_nodes, string node)
{
	if (find(selected_nodes.begin(), selected_nodes.end(), node) == selected_nodes.end())
	{
		selected_nodes.push_back(node);
	}
}

void AddNodeAvailableEdges(Graph& graph, vector<EdgePath>& selected_edges, vector<EdgePath>& available_edges, string node_label)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> node_edges = graph.GetConnectedEdges(node_label);

	for (edge_i = node_edges.begin(); edge_i != node_edges.end(); edge_i++)
	{
		if (!IsEdgeInVector(selected_edges, *edge_i) && !IsEdgeInVector(available_edges, *edge_i))
		{
			EdgePath edge_path = CreateEdgePath(*edge_i, node_label);
			available_edges.push_back(edge_path);
		}
	}
}

vector<PrimResult> MapMinimumSpanningTree(vector<EdgePath> selected_edges)
{
	vector<PrimResult> results;
	vector<EdgePath>::iterator edge_i;

	for (edge_i = selected_edges.begin(); edge_i != selected_edges.end(); edge_i++)
	{
		EdgePath edge = *edge_i;

		results.push_back({ edge.origin, edge.destination, edge.label });
	}

	return results;
}

vector<PrimResult> Prim::FindMinimumSpanningTree()
{
	// The selected subgraph
	vector<EdgePath> selected_edges;

	// The edges available to be selected
	vector<EdgePath> available_edges;

	// Nodes list
	vector<string> pending_nodes = _graph.GetNodeLabels();
	
	// Select random starting point
	string starting_node = PopNode(pending_nodes, string());
	vector<string> selected_nodes = { starting_node };

	AddNodeAvailableEdges(_graph, selected_edges, available_edges, starting_node);

	do
	{
		// Get closest edge
		EdgePath closest_edge = GetClosestEdge(available_edges);

		// Move nodes from pending to selected nodes
		SelectNode(selected_nodes, closest_edge.destination);
		PopNode(pending_nodes, closest_edge.destination);

		// Add to path pool
		selected_edges.push_back(closest_edge);

		// Add new node available edges
		AddNodeAvailableEdges(_graph, selected_edges, available_edges, closest_edge.destination);
		PopEdge(available_edges, closest_edge.label);

	} while (!pending_nodes.empty());

	return MapMinimumSpanningTree(selected_edges);
}

bool Prim::IsGraphValid(Graph graph)
{
	// Prim only works on non directional graphs
	return IsNonDirectional(graph);
}