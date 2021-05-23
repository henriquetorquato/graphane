#include "csv_graph_reader.h"
#include "node.h"
#include "graph.h"
#include <sstream>
#include <iostream>
#include "graph_builder.h"

using namespace std;

const char FileSeparator = ';';
const string Empty = "0";
const int StartingChar = 'A';
const int EndingChar = 'Z';

CsvGraphReader::CsvGraphReader(string filename)
{
	_filename = filename;
}

Graph CsvGraphReader::ReadGraph()
{
	try
	{
		ifstream file = GetFileStream(_filename);

		GraphBuilder graph_builder;

		vector<string> nodes = ReadNodes(file);
		graph_builder.AddNodes(nodes);

		char n_value;
		int line_index = 0;
		int edge_index = 0;
		string line;

		while (getline(file, line))
		{
			int col_index = 0;
			int char_index = 0;

			stringstream sstream(line), next_value;
			string node_a = nodes.at(line_index);

			while (sstream >> n_value)
			{
				char_index++;
				if (n_value != FileSeparator)
				{
					next_value << n_value;

					/*
					* The last character does not have the separator,
					* this "if" is so that this last character is processed.
					*/
					if (char_index < line.length())
					{
						continue;
					}
				}

				if (next_value.str() == Empty)
				{
					col_index++;
					next_value.str(string());

					continue;
				}

				string node_b = nodes.at(col_index);

				string edge_label = to_string(edge_index);
				int edge_value = stoi(next_value.str());

				graph_builder.AddEdge(edge_label, edge_value, node_a, node_b);

				next_value.str(string());
				col_index++;
				edge_index++;
			}

			line_index++;
		}

		file.close();
		return graph_builder.Build();
	}
	catch (runtime_error)
	{
		cout
			<< "Failed to open file " << _filename
			<< endl;
	}

	Graph null_graph;
	return null_graph;
}

ifstream CsvGraphReader::GetFileStream(string filename)
{
	// Create input stream from file
	ifstream file(filename);

	if (!file.is_open())
	{
		throw runtime_error("Unable to open file.");
	}

	return file;
}

vector<string> CsvGraphReader::ReadHeader(ifstream &file)
{
	string line;
	vector<string> colnames;
	char n_value;

	if (file.good())
	{
		getline(file, line);
		stringstream sstream(line), next_value;

		while (sstream >> n_value)
		{
			if (n_value != FileSeparator)
			{
				next_value << n_value;
				continue;
			}

			colnames.push_back(next_value.str());
			next_value.str(string());
		}

		// Add last col
		colnames.push_back(next_value.str());
	}

	try 
	{
		// Header check
		stoi(colnames[0]);
		return vector<string>();
	}
	catch (invalid_argument)
	{
		// If breaks on str to int cast then there are headers
		return colnames;
	}
}

vector<string> CsvGraphReader::ReadNodes(ifstream& file)
{
	vector<string> nodes;
	vector<string> headers = ReadHeader(file);

	if (headers.size() > 0)
	{
		return headers;
	}
	else
	{
		for (int i = 0; i < headers.size(); i++)
		{
			int c_value = StartingChar + i;

			string label = (c_value > EndingChar)
				? GenerateLabel(c_value)
				: string(1, c_value);

			nodes.push_back(label);
		}
	}

	return nodes;
}

string CsvGraphReader::GenerateLabel(int value)
{
	int c_amount = (int) ceil(value / EndingChar);
	int diff = EndingChar - value;

	string label;
	for (int i = 0; i < c_amount - 1; i++)
	{
		label.append(string(1, (char)StartingChar));
	}

	label.append(string(1, (char)diff));
	return label;
}