#include "graph.h"
#include <stdexcept>

void Graph::InitializeMaps()
{
	// Reset maps
	node_map.clear();
	connected_edges_map.clear();
	node_neighbours_map.clear();

	vector<Node>::iterator node_i;
	for (node_i = _nodes.begin(); node_i != _nodes.end(); node_i++)
	{
		// Map node label to instance
		Node node(*node_i);
		node_map.insert(make_pair(node.GetLabel(), node));

		// Map node label to edge instances
		vector<Edge>::iterator edge_i;
		vector<Edge> connected_edges;
		vector<string> neighbours;

		for (edge_i = _edges.begin(); edge_i != _edges.end(); edge_i++)
		{
			Edge edge = *edge_i;

			/*
			* The node is only path if it's the origin of a directional edge,
			* or if the edge is bidirectional.
			*/
			bool isPath = edge.GetNodeA() == node.GetLabel()
				|| (edge.ContainsNode(node.GetLabel()) && edge.IsBidirectional());

			if (isPath)
			{				
				connected_edges.push_back(edge);
				neighbours.push_back(edge.GetNeighbour(node.GetLabel()));
			}
		}

		connected_edges_map.insert(make_pair(node.GetLabel(), connected_edges));
		node_neighbours_map.insert(make_pair(node.GetLabel(), neighbours));
	}
}

vector<string> Graph::GetNodeLabels()
{
	vector<string> result;
	map<string, Node>::iterator node_i;

	for (node_i = node_map.begin(); node_i != node_map.end(); node_i++)
	{
		result.push_back(node_i->first);
	}

	return result;
}

vector<string> Graph::GetNeighbours(string label)
{
	map<string, vector<string>>::iterator it
		= node_neighbours_map.find(label);

	if (it == node_neighbours_map.end())
	{
		return vector<string>();
	}

	return it->second;
}

vector<Edge> Graph::GetConnectedEdges(string label)
{
	map<string, vector<Edge>>::iterator it
		= connected_edges_map.find(label);

	if (it == connected_edges_map.end())
	{
		return vector<Edge>();
	}

	return it->second;
}