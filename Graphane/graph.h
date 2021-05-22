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
	// Map node label to node instance
	map<string, Node> node_map;

	// Map node label to connected edges
	map<string, vector<Edge>> connected_edges_map;

	void InitializeMaps(vector<Node> nodes, vector<Edge> edges);

public:
	Graph(vector<Node> nodes, vector<Edge> edges)
	{
		InitializeMaps(nodes, edges);
	}

	Graph()
	{ }

	vector<string> GetNodeLabels();
	vector<Edge> GetConnectedEdges(string label);
};