#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "edge.h"
#include "graph.h"

class CsvGraphReader
{
private:
	std::string m_filename;
	std::ifstream GetFileStream(std::string filename);
	std::vector<char> GetFileHeaders(std::ifstream &file);
	std::vector<Edge> CreateEdges(std::ifstream& file);
	std::string GenerateLabel(int value);

public:
	CsvGraphReader(std::string filename);
	Graph ReadGraph();
};