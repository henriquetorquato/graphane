// https://forums.codeguru.com/showthread.php?560037-RESOLVED-VS-2017-and-Windows-h-issue&s=682b843e305564fd7790fe152b9231bf&p=2216871#post2216871
#define _HAS_STD_BYTE 0

#include "csv_graph_reader.h"
#include "string_utils.h"
#include "dijkstra.h"
#include "prim.h"
#include "ford_fulkerson.h"
#include "kosaraju.h"

#include <iostream>
#include <Windows.h>

using namespace std;

const string TARGET_FILE = "\\Tests\\test3_directional.csv";
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

int main()
{
	string path(GetExecutingPath());
	path.append(TARGET_FILE);

    CsvGraphReader reader(path);
    Graph graph = reader.ReadGraph();

	// Dijkstra
	cout << "Shortest path from `" << DIJKSTRA_ORIGIN << "` (Dijkstra):" << endl;

	Dijkstra dijkstra(graph);
	DijkstraResult shortest_paths = dijkstra.FindShortestPath(DIJKSTRA_ORIGIN);
	dijkstra.DisplayResult(shortest_paths);

	cout << "\n" << endl;

	// Prim
	cout << "Minimum spanning tree (Prim):" << endl;

	if (Prim::IsGraphValid(graph))
	{
		Prim prim(graph);
		PrimResult minimum_spanning_tree = prim.FindMinimumSpanningTree();
		prim.DisplayResult(minimum_spanning_tree);
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
		FordFulkersonResult maximum_flow = ford_fulkerson.FindMaximumFlow(FORD_FULKERSON_SOURCE, FORD_FULKERSON_TERMINAL);
		ford_fulkerson.DisplayResult(maximum_flow);
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

	// Kosaraju
	cout << "Strongly Connected Components (Kosaraju):" << endl;

	Kosaraju kosaraju(graph);
	KosarajuResult strongly_connected_components = kosaraju.FindStronglyConnectedComponents();
	kosaraju.DisplayResult(strongly_connected_components);

	cout << "\n" << endl;
}