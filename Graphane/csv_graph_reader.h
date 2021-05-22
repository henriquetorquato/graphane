#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "edge.h"
#include "graph.h"

using namespace std;

class CsvGraphReader
{
private:
	string _filename;

	ifstream GetFileStream(string filename);
	string GenerateLabel(int value);
	vector<string> ReadNodes(ifstream& file);
	vector<string> ReadHeader(ifstream& file);

public:
	CsvGraphReader(string filename);
	Graph ReadGraph();
};