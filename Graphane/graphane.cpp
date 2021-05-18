// https://forums.codeguru.com/showthread.php?560037-RESOLVED-VS-2017-and-Windows-h-issue&s=682b843e305564fd7790fe152b9231bf&p=2216871#post2216871
#define _HAS_STD_BYTE 0

#include "csv_graph_reader.h"
#include "string_utils.h"
#include "dijkstra.h"
#include "prim.h"
#include <iostream>
#include <Windows.h>

using namespace std;

const string TARGET_FILE = "test2.csv";
const string DIRECTORY_SEPARATOR = "\\";

// https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf
static string GetExecutingPath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of(DIRECTORY_SEPARATOR);

	return string(buffer).substr(0, pos);
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

int main()
{
	string path(GetExecutingPath());
	path.append(DIRECTORY_SEPARATOR);
	path.append(TARGET_FILE);

    CsvGraphReader reader(path);
    Graph graph = reader.ReadGraph();

	// Dijkstra
	cout << "Shortest path from 'G' (Dijkstra):" << endl;

	Dijkstra dijkstra(graph);
	vector<DijkstraResult> shortestPaths = dijkstra.FindShortestPath("G");
	DisplayDijkstraShortestPaths(shortestPaths);

	cout << "\n" << endl;

	// Prim
	cout << "Minimum spanning tree (Prim):" << endl;

	Prim prim(graph);
	vector<PrimResult> minimumSpanningTree = prim.FindMinimumSpanningTree();
	DisplayPrimMinimumSpanningTree(minimumSpanningTree);
}