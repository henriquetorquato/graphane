// https://forums.codeguru.com/showthread.php?560037-RESOLVED-VS-2017-and-Windows-h-issue&s=682b843e305564fd7790fe152b9231bf&p=2216871#post2216871
#define _HAS_STD_BYTE 0

#include "csv_graph_reader.h"
#include "string_utils.h"
#include "dijkstra.h"
#include "prim.h"
#include "ford_fulkerson.h"

#include <iostream>
#include <Windows.h>

using namespace std;

const string TARGET_FILE = "\\Tests\\test4_max_flow_19.csv";
const string DIRECTORY_SEPARATOR = "\\";

const string DIJKSTRA_ORIGIN = "A";
const string FORD_FULKERSON_SOURCE = "S";
const string FORD_FULKERSON_TERMINAL = "T";

// https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf
static string GetExecutingPath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string path(buffer);

	size_t position(0);
	vector<size_t> positions;
	
	while (position != string::npos)
	{
		position = path.find(DIRECTORY_SEPARATOR, position + 1);
		positions.push_back(position);
	}

	// Go back two dir's
	return path.substr(0, positions.at(positions.size() - 3));
}

static void DisplayDijkstraShortestPaths(vector<DijkstraResult> shortest_paths)
{
	vector<DijkstraResult>::iterator it;
	for (it = shortest_paths.begin(); it != shortest_paths.end(); it++)
	{
		DijkstraResult result(*it);

		cout
			<< result.origin << " -> " << result.destination
			<< " | Path: " << ToString(result.path, DEFAULT_LIST_SEPARATOR)
			<< " | Weight: " << result.weight
			<< endl;
	}
}

static void DisplayPrimMinimumSpanningTree(vector<PrimResult> minimum_spanning_tree)
{
	vector<string> edges;
	vector<PrimResult>::iterator it;

	for (it = minimum_spanning_tree.begin(); it != minimum_spanning_tree.end(); it++)
	{
		PrimResult result(*it);
		edges.push_back(result.origin + result.destination);
	}

	cout << ToString(edges, DEFAULT_LIST_SEPARATOR) << endl;
}

static void DisplayFordFulkersonMaximumFlow(int maximum_flow)
{
	cout << to_string(maximum_flow) << endl;
}

int main()
{
	string path(GetExecutingPath());
	path.append(TARGET_FILE);

    CsvGraphReader reader(path);
    Graph graph = reader.ReadGraph();

	// Dijkstra
	cout << "Shortest path from `" << DIJKSTRA_ORIGIN << "` (Dijkstra):" << endl;

	Dijkstra dijkstra(graph);
	vector<DijkstraResult> shortest_paths = dijkstra.FindShortestPath(DIJKSTRA_ORIGIN);
	DisplayDijkstraShortestPaths(shortest_paths);

	cout << "\n" << endl;

	// Prim
	cout << "Minimum spanning tree (Prim):" << endl;

	if (Prim::IsGraphValid(graph))
	{
		Prim prim(graph);
		vector<PrimResult> minimum_spanning_tree = prim.FindMinimumSpanningTree();
		DisplayPrimMinimumSpanningTree(minimum_spanning_tree);
	}
	else
	{
		cout << "Prim's algorithm cannot process this graph!" << endl;
	}

	cout << "\n" << endl;

	// Ford-Fulkerson
	cout << "Maximum flow from `"
		<< FORD_FULKERSON_SOURCE
		<< "` to `"
		<< FORD_FULKERSON_TERMINAL
		<< "` (Ford-Fulkerson):" << endl;

	if (FordFulkerson::IsGraphValid(graph, FORD_FULKERSON_SOURCE, FORD_FULKERSON_TERMINAL))
	{
		FordFulkerson ford_fulkerson(graph);
		int maximum_flow = ford_fulkerson.FindMaximumFlow(FORD_FULKERSON_SOURCE, FORD_FULKERSON_TERMINAL);
		DisplayFordFulkersonMaximumFlow(maximum_flow);
	}
	else
	{
		cout << "Ford-Fulkerson's algorithm cannot process this graph with source `"
			<< FORD_FULKERSON_SOURCE
			<< "` and terminal `"
			<< FORD_FULKERSON_TERMINAL
			<< "`!"
			<< endl;
	}

	cout << "\n" << endl;
}