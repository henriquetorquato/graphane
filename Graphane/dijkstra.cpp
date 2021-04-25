#include "dijkstra.h"
#include "string_utils.h"
#include <tuple>
#include <sstream>
#include <iostream>

using namespace std;

struct NodeWeight
{
	string node;
	string origin;
	int weight = 0;
};

tuple<NodeWeight, int> GetSmallestWeight(vector<NodeWeight> weights)
{
	int index = 0;
	int smallest_index = 0;

	NodeWeight smallest;
	vector<NodeWeight>::iterator weights_i;

	for (weights_i = weights.begin(); weights_i != weights.end(); weights_i++, index++)
	{
		NodeWeight current = *weights_i;
		if (index == 0 || current.weight < smallest.weight)
		{
			smallest = current;
			smallest_index = index;
		}
	}

	return { smallest, smallest_index };
}

int FindNode(string node_label, vector<NodeWeight> nodes)
{
	int index = 0;
	vector<NodeWeight>::iterator node_i;

	for (node_i = nodes.begin(); node_i != nodes.end(); node_i++, index++)
	{
		string node_weight_label = (*node_i).node;
		if (node_label == node_weight_label)
		{
			return index;
		}
	}

	return -1;
}

bool ContainsNodeLabel(string node_label, vector<NodeWeight> nodes)
{
	return FindNode(node_label, nodes) > -1;
}

void DisplayShortestPath(string origin_label, vector<NodeWeight> result)
{
	vector<NodeWeight>::iterator node_i;
	for (node_i = result.begin(); node_i != result.end(); node_i++)
	{
		NodeWeight node_weight = *node_i;

		// Skip origin path
		if (node_weight.origin == string())
		{
			continue;
		}

		// Save destination information
		string detination_label = node_weight.node;
		int destination_weight = node_weight.weight;

		vector<string> path;
		bool pathComplete = false;

		do
		{
			path.push_back(node_weight.node);
			
			if (node_weight.origin == string())
			{
				pathComplete = true;
			}
			else
			{
				// Follow path
				int next_index = FindNode(node_weight.origin, result);
				node_weight = result.at(next_index);
			}

		} while (!pathComplete);

		reverse(path.begin(), path.end());
		string path_out = ToString(path, DEFAULT_LIST_SEPARATOR);

		cout
			<< origin_label << " -> " << detination_label
			<< " | Path: " << path_out
			<< " | Weight: " << destination_weight
			<< endl;
	}
}

void Dijkstra::FindShortestPath(string origin_label)
{
	vector<NodeWeight> weights;
	vector<NodeWeight> result;

	// Initializes the weight of the start
	NodeWeight origin_weight = { origin_label, string(), 0 };
	weights.push_back(origin_weight);

	int weight_index;
	NodeWeight current_weight;

	do
	{
		tie(current_weight, weight_index) = GetSmallestWeight(weights);

		vector<Edge>::iterator edges_i;
		vector<Edge> edges = m_graph.GetEdges(current_weight.node);

		for (edges_i = edges.begin(); edges_i != edges.end(); edges_i++)
		{
			Edge edge = *edges_i;
			Node* next_node = edge.GetNodeNeighbour(current_weight.node);

			if (ContainsNodeLabel(next_node->GetLabel(), result))
			{
				continue;
			}

			int weight = current_weight.weight + edge.GetValue();

			NodeWeight next_weight = { next_node->GetLabel(), current_weight.node, weight };
			weights.push_back(next_weight);
		}

		if (!ContainsNodeLabel(current_weight.node, result))
		{
			result.push_back(current_weight);
		}

		weights.erase(weights.begin() + weight_index);

	} while (!weights.empty());

	DisplayShortestPath(origin_label, result);
}