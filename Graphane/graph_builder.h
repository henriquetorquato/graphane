#pragma once
#include <string>
#include "edge.h"
#include "graph.h"

using namespace std;

/*
* No, this is not a builder pattern.
* Now go away!
*/
class GraphBuilder
{
private:
	vector<Node> _nodes;
	vector<Edge> _edges;

	optional<int> FindNode(Node node);
	optional<int> FindEdge(Edge edge);
	bool ContainsNodeLabel(string label);
	bool ContainsEdgeLabel(string label);

public:
	void AddNode(string label);
	void AddNodes(vector<string> labels);
	void AddEdge(string label, int value, string node_a, string node_b, EdgeType type = EdgeType::Directional);

	Graph Build();
};