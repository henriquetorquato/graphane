#pragma once
#include <vector>
#include <optional>
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
	bool ContainsEdgeLabel(string label);

public:
	void AddNode(Node node);
	void AddEdge(Edge edge);

	void AddNodes(vector<Node> nodes);
	void AddEdges(vector<Edge> edges);

	Node GetNode(string label);
	vector<string> GetNodeLabels();

	Node* GetNodeAt(int index);
	Edge* GetEdgeAt(int index);

	vector<Node> GetNodes() { return nodes; }
	vector<Edge> GetEdges() { return edges; }
	vector<Edge> GetEdges(string node_label);

	optional<int> FindNode(Node node);
	optional<int> FindEdge(Edge edge);
};