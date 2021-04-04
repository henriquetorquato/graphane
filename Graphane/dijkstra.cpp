#include "dijkstra.h";
#include <tuple>

struct NodeWeight
{
	std::string node;
	std::string origin;
	int weight;
};

std::tuple<NodeWeight, int> GetSmallestWeight(std::vector<NodeWeight> weights)
{
	int index = 0;
	int smallest_index = 0;

	NodeWeight smallest;
	std::vector<NodeWeight>::iterator weights_i;

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

bool IsNodeProcessed(Node* node, std::vector<NodeWeight> processed_nodes)
{
	std::vector<NodeWeight>::iterator node_i;
	for (node_i = processed_nodes.begin(); node_i != processed_nodes.end(); node_i++)
	{
		std::string processed_node_label = (*node_i).node;
		if (node->GetLabel() == processed_node_label)
		{
			return true;
		}
	}

	return false;
}

void Dijkstra::FindShortestPath(std::string origin_label)
{
	std::vector<NodeWeight> weights;
	std::vector<NodeWeight> result;

	// Initializes the weight of the start
	NodeWeight origin_weight = { origin_label, std::string(), 0 };
	weights.push_back(origin_weight);

	int weight_index;
	NodeWeight current_weight;

	do
	{
		std::tie(current_weight, weight_index) = GetSmallestWeight(weights);

		std::vector<Edge>::iterator edges_i;
		std::vector<Edge> edges = m_graph.GetEdges(current_weight.node);

		for (edges_i = edges.begin(); edges_i != edges.end(); edges_i++)
		{
			Edge edge = *edges_i;
			Node* next_node = edge.GetNodeNeighbour(current_weight.node);

			if (IsNodeProcessed(next_node, result))
			{
				continue;
			}

			int weight = current_weight.weight + edge.GetValue();

			NodeWeight next_weight = { next_node->GetLabel(), current_weight.node, weight };
			weights.push_back(next_weight);
		}

		result.push_back(current_weight);
		weights.erase(weights.begin() + weight_index);

	} while (!weights.empty());
}