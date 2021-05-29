#include "dijkstra.h"
#include "string_utils.h"
#include <tuple>
#include <sstream>
#include <iostream>

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

int FindNodeIndex(string node_label, vector<NodeWeight> nodes)
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

NodeWeight FindNode(string node_label, vector<NodeWeight> nodes)
{
	int node_index = FindNodeIndex(node_label, nodes);
	
	if (node_index == -1)
	{
		throw new runtime_error("Node not found on weight list");
	}

	return nodes.at(node_index);
}

bool ContainsNodeLabel(string node_label, vector<NodeWeight> nodes)
{
	return FindNodeIndex(node_label, nodes) > -1;
}

DijkstraShortestPath MapDijkstraResult(string origin_label, string destination_label, vector<NodeWeight> node_weights)
{
	vector<string> path;
	bool pathComplete = false;

	NodeWeight node_weight(FindNode(destination_label, node_weights));
	int destination_weight = node_weight.weight;

	do
	{
		path.push_back(node_weight.node);

		if (node_weight.node == origin_label)
		{
			pathComplete = true;
		}
		else
		{
			// Follow path
			node_weight = FindNode(node_weight.origin, node_weights);
		}

	} while (!pathComplete);

	reverse(path.begin(), path.end());
	return { origin_label, destination_label, path, destination_weight };
}

DijkstraResult MapDijkstraResults(string origin_label, string destination_label, vector<NodeWeight> node_weights)
{
	if (destination_label != string())
	{
		return {
			{ MapDijkstraResult(origin_label, destination_label, node_weights) }
		};
	}

	vector<DijkstraShortestPath> results;
	vector<NodeWeight>::iterator node_i;

	for (node_i = node_weights.begin(); node_i != node_weights.end(); node_i++)
	{
		NodeWeight node_weight = *node_i;

		// Skip origin path
		if (node_weight.node == origin_label)
		{
			continue;
		}
		
		DijkstraShortestPath result = MapDijkstraResult(origin_label, node_weight.node, node_weights);
		results.push_back(result);
	}

	return { results };
}

DijkstraResult Dijkstra::FindShortestPath(string origin_label, string destination_label)
{
	vector<NodeWeight> weights;
	vector<NodeWeight> result;

	// Initializes the weight of the start
	NodeWeight origin_weight = { origin_label, string(), 0 };
	weights.push_back(origin_weight);

	int weight_index;
	NodeWeight current_weight;
	bool destination_found = false;

	do
	{
		tie(current_weight, weight_index) = GetSmallestWeight(weights);

		vector<Edge>::iterator edges_i;
		vector<Edge> edges = _graph.GetConnectedEdges(current_weight.node);

		for (edges_i = edges.begin(); edges_i != edges.end(); edges_i++)
		{
			Edge edge = *edges_i;
			string next_node = edge.GetNeighbour(current_weight.node);

			if (ContainsNodeLabel(next_node, result))
			{
				continue;
			}

			int weight = current_weight.weight + edge.GetValue();

			NodeWeight next_weight = { next_node, current_weight.node, weight };
			weights.push_back(next_weight);
		}

		if (!ContainsNodeLabel(current_weight.node, result))
		{
			result.push_back(current_weight);

			if (destination_label != string()
				&& current_weight.node == destination_label)
			{
				destination_found = true;
			}
		}

		weights.erase(weights.begin() + weight_index);

	} while (!weights.empty() && !destination_found);

	return MapDijkstraResults(origin_label, destination_label, result);
}

void Dijkstra::DisplayResult(DijkstraResult result)
{
	vector<DijkstraShortestPath>::iterator it;
	for (it = result.paths.begin(); it != result.paths.end(); it++)
	{
		DijkstraShortestPath result(*it);

		cout
			<< result.origin << " -> " << result.destination
			<< " | Path: " << ToString(result.path, DEFAULT_LIST_SEPARATOR)
			<< " | Weight: " << result.weight
			<< endl;
	}
}