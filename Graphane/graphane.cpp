#include "csv_graph_reader.h"
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
	dijkstra.FindShortestPath("G");

	cout << "\n" << endl;

	// Prim
	cout << "Minimum spanning tree (Prim):" << endl;
	Prim prim(graph);
	prim.FindMinimumSpanningTree();
}