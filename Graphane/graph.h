#pragma once
#include <vector>
#include <optional>
#include <map>
#include <memory>
#include "node.h"
#include "edge.h"

using namespace std;

class Graph
{
private:
	vector<Node> _nodes;
	vector<Edge> _edges;

	// Map node label to node instance
	map<string, Node> node_map;

	// Map node label to connected edges
	map<string, vector<Edge>> connected_edges_map;

	void InitializeMaps();

public:
	Graph(vector<Node> nodes, vector<Edge> edges)
	{
		_nodes = nodes;
		_edges = edges;
		InitializeMaps();
	}

	Graph()
	{ }

	vector<Edge> GetEdges() { return _edges; }

	vector<string> GetNodeLabels();
	vector<Edge> GetConnectedEdges(string label);
};