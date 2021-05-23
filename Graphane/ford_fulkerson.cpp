#include "ford_fulkerson.h"
#include <queue>
#include <memory>

struct FlowCapacity
{
	string origin;
	string destination;
	int value;
	int capacity;
};

map<string, FlowCapacity> CreateResidualGraph(Graph graph)
{
	map<string, FlowCapacity> residual_graph;

	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge(*edge_i);

		// represents the path origin -> destination
		string key = edge.GetNodeA() + edge.GetNodeB();
		FlowCapacity capacity = { edge.GetNodeA(), edge.GetNodeB(), 0, edge.GetValue() };

		residual_graph.insert(make_pair(key, capacity));

		// If the edge is bi-directional, then there is also a reverse flow
		if (edge.IsBidirectional())
		{
			key = edge.GetNodeB() + edge.GetNodeA();
			capacity = { edge.GetNodeB(), edge.GetNodeA(), 0, edge.GetValue() };

			residual_graph.insert(make_pair(key, capacity));
		}
	}

	return residual_graph;
}

// The use of BFS on Ford-Fulkerson's Algorithm also caracterizes it as Edmonds-Karp's Algorithm.
bool BreadthFirstSeach(Graph graph, map<string, FlowCapacity> residual_graph, string source, string terminal, vector<FlowCapacity>& path)
{
	queue<string> node_queue;
	vector<string> visited_nodes;

	// Add source to queue
	node_queue.push(source);

	while (!node_queue.empty())
	{
		string next_node = node_queue.front();
		node_queue.pop();

		vector<Edge>::iterator edge_i;
		vector<Edge> connected_edges = graph.GetConnectedEdges(next_node);

		for (edge_i = connected_edges.begin(); edge_i != connected_edges.end(); edge_i++)
		{
			Edge edge(*edge_i);	
			string destination = edge.GetNeighbour(next_node);

			string key = next_node + destination;
			FlowCapacity flow = residual_graph[key];

			// TODO: Check if path value is < capacity and reverse path is > 0

			if (flow.destination == terminal)
			{
				path.push_back(flow);
				return true;
			}

			// Check if node was visited
			bool visited = find(visited_nodes.begin(), visited_nodes.end(), flow.destination)
				!= visited_nodes.end();

			if (visited)
			{
				continue;
			}

			node_queue.push(destination);
			path.push_back(flow);
		}

		visited_nodes.push_back(next_node);
	}

	return false;
}

int FordFulkerson::FindMaximumFlow(string source, string terminal)
{
	/*
	* Check:
	* https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
	* https://www.youtube.com/watch?v=Tl90tNtKvxs
	*/

	// Create residual graph
	map<string, FlowCapacity> residual_graph = CreateResidualGraph(_graph);

	int max_flow = 0;
	vector<FlowCapacity> path;

	// While there is a path between the source and the terminal
	while (BreadthFirstSeach(_graph, residual_graph, source, terminal, path))
	{
		// Find bottleneck capacity
		FlowCapacity current_flow = path.back();		
		bool source_reached = false;

		int bottleneck_capacity = current_flow.capacity;
		vector<pair<string, string>> walked_path;

		while (!source_reached)
		{
			if (current_flow.capacity < bottleneck_capacity)
			{
				bottleneck_capacity = current_flow.capacity;
			}

			if (current_flow.origin == source)
			{
				// Add last part of the path
				walked_path.push_back(
					make_pair(current_flow.origin, current_flow.destination));

				source_reached = true;
				continue;
			}

			// Walk path
			FlowCapacity flow;
			vector<FlowCapacity>::iterator flow_i;
			for (flow_i = path.begin(); flow_i != path.end(); flow_i++)
			{
				flow = *flow_i;

				if (flow.destination == current_flow.origin)
				{
					break;
				}
			}

			walked_path.push_back(
				make_pair(current_flow.origin, current_flow.destination));

			current_flow = flow;
		}

		// Update residual graph
		vector<pair<string, string>>::iterator path_i;
		for (path_i = walked_path.begin(); path_i != walked_path.end(); path_i++)
		{
			pair<string, string> walked_section(*path_i);

			string key = walked_section.first + walked_section.second;
			string inverseKey = walked_section.second + walked_section.first;

			residual_graph[key].value += bottleneck_capacity;

			// TODO: Fix this, check if this is needed
			residual_graph[inverseKey].value -= bottleneck_capacity;
		}

		path.clear();
		max_flow += bottleneck_capacity;
	}

	return max_flow;
}

bool FordFulkerson::IsGraphValid(Graph graph, string source, string terminal)
{
	return IsSourceValid(graph, source) && IsTerminalValid(graph, terminal);
}

// The source can't have any edges directed to it
bool FordFulkerson::IsSourceValid(Graph graph, string source)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge = (*edge_i);

		/*
		* If it's a directional edge destination
		* or, if it's part of a bi-directional edge.
		*/
		bool isInvalid = (edge.IsDirectional() && edge.GetNodeB() == source)
			|| (edge.IsBidirectional() && edge.ContainsNode(source));

		if (isInvalid)
		{
			return false;
		}
	}

	return true;
}

// The terminal can't have any edges originating from it
bool FordFulkerson::IsTerminalValid(Graph graph, string terminal)
{
	vector<Edge>::iterator edge_i;
	vector<Edge> edges = graph.GetEdges();

	for (edge_i = edges.begin(); edge_i != edges.end(); edge_i++)
	{
		Edge edge = (*edge_i);

		/*
		* If it's a directional edge origin
		* or, if it's part of a bi-directional edge.
		*/
		bool isInvalid = (edge.IsDirectional() && edge.GetNodeA() == terminal)
			|| (edge.IsBidirectional() && edge.ContainsNode(terminal));

		if (isInvalid)
		{
			return false;
		}
	}

	return true;
}