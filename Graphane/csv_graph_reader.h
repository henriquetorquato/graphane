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
	std::vector<Node> CreateNodes(std::ifstream& file);
	std::string GenerateLabel(int value);
	std::vector<std::string> ReadHeader(std::ifstream& file);

public:
	CsvGraphReader(std::string filename);
	Graph ReadGraph();
};