#include "csv_graph_reader.h"
#include "dijkstra.h"
#include <iostream>
#include <Windows.h>

const std::string TARGET_FILE = "test2.csv";
const std::string DIRECTORY_SEPARATOR = "\\";

// https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf
static std::string GetExecutingPath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of(DIRECTORY_SEPARATOR);

	return std::string(buffer).substr(0, pos);
}

int main()
{
	std::string path(GetExecutingPath());
	path.append(DIRECTORY_SEPARATOR);
	path.append(TARGET_FILE);

    CsvGraphReader reader(path);
    Graph graph = reader.ReadGraph();

	Dijkstra dijkstra(graph);
	dijkstra.FindShortestPath("G");
}