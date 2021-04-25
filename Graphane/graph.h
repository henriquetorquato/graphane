#pragma once
#include <vector>
#include "node.h"
#include "edge.h"

using namespace std;

class Graph
{
private:
	vector<Node> nodes;
	vector<Edge> edges;
	bool ContainsNode(Node node);
	bool ContainsNodeLabel(string label);
	bool ContainsEdge(Edge edge);

public:
	void AddNode(Node node);
	void AddNodes(vector<Node> nodes);
	Node GetNode(string label);
	Node* GetNodeAt(int index);
	vector<Node> GetNodes() { return nodes; }
	vector<string> GetNodeLabels();
	int FindNode(string label);

	void AddEdge(Edge edge);
	void AddEdges(vector<Edge> edges);
	vector<Edge> GetEdges() { return edges; }
	vector<Edge> GetEdges(string node_label);
};