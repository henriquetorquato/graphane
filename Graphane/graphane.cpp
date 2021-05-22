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

const string TARGET_FILE = "\\Tests\\test3_directional.csv";
const string DIRECTORY_SEPARATOR = "\\";

const string DIJKSTRA_ORIGIN = "A";
const string FORD_FULKERSON_SOURCE = "A";
const string FORD_FULKERSON_TERMINAL = "G";

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

static void DisplayDijkstraShortestPaths(vector<DijkstraResult> shortestPaths)
{
	vector<DijkstraResult>::iterator it;
	for (it = shortestPaths.begin(); it != shortestPaths.end(); it++)
	{
		DijkstraResult result(*it);

		cout
			<< result.origin << " -> " << result.destination
			<< " | Path: " << ToString(result.path, DEFAULT_LIST_SEPARATOR)
			<< " | Weight: " << result.weight
			<< endl;
	}
}

static void DisplayPrimMinimumSpanningTree(vector<PrimResult> minimumSpanningTree)
{
	vector<string> edges;
	vector<PrimResult>::iterator it;

	for (it = minimumSpanningTree.begin(); it != minimumSpanningTree.end(); it++)
	{
		PrimResult result(*it);
		edges.push_back(result.origin + result.destination);
	}

	cout << ToString(edges, DEFAULT_LIST_SEPARATOR) << endl;
}

static void DisplayFordFulkersonMaximumFlow(vector<FordFulkersonResult> maximumFlow)
{

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
	vector<DijkstraResult> shortestPaths = dijkstra.FindShortestPath(DIJKSTRA_ORIGIN);
	DisplayDijkstraShortestPaths(shortestPaths);

	cout << "\n" << endl;

	// Prim
	cout << "Minimum spanning tree (Prim):" << endl;

	if (Prim::IsGraphValid(graph))
	{
		Prim prim(graph);
		vector<PrimResult> minimumSpanningTree = prim.FindMinimumSpanningTree();
		DisplayPrimMinimumSpanningTree(minimumSpanningTree);
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

	if (FordFulkerson::IsGraphValid(graph, "A", "G"))
	{
		FordFulkerson fordFulkerson(graph);
		vector<FordFulkersonResult> maximumFlow = fordFulkerson.FindMaximumFlow("A", "G");
		DisplayFordFulkersonMaximumFlow(maximumFlow);
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