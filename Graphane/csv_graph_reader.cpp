#include "csv_graph_reader.h"
#include "node.h"
#include "graph.h"
#include <sstream>
#include <iostream>

const char FileSeparator = ';';
const char Connected = '1';
const char Empty = '0';
const int StartingChar = 'A';
const int EndingChar = 'Z';

CsvGraphReader::CsvGraphReader(std::string filename)
{
	m_filename = filename;
}

Graph CsvGraphReader::ReadGraph()
{
	try
	{
		std::ifstream file = GetFileStream(m_filename);
		std::vector<Edge> edges = CreateEdges(file);

		int node_index = 0;
		std::string line;
		char n_value;
		Graph graph;

		while (std::getline(file, line))
		{
			std::string label = std::to_string(node_index);
			Node node(label);
			Node& node_ref = std::ref(node);

			std::stringstream sstream(line);
			int col_index = 0;

			while (sstream >> n_value)
			{
				if (sstream.peek() == FileSeparator)
				{
					sstream.ignore();
				}

				if (n_value == Connected)
				{
					edges.at(col_index).AddNode(node_ref);
				}

				col_index++;
			}

			graph.AddNode(node_ref);
			node_index++;
		}

		for (Edge edge : edges)
		{
			Edge edge_ref = std::ref(edge);
			graph.AddEdge(edge_ref);
		}

		file.close();
		return graph;
	}
	catch (std::runtime_error)
	{
		std::cout
			<< "Failed to open file " << m_filename
			<< std::endl;
	}

	Graph null_graph;
	return null_graph;
}

std::ifstream CsvGraphReader::GetFileStream(std::string filename)
{
	// Create input stream from file
	std::ifstream file(filename);

	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file.");
	}

	return file;
}

std::vector<char> CsvGraphReader::GetFileHeaders(std::ifstream &file)
{
	std::string line;
	std::vector<char> colnames;
	char n_value;

	if (file.good())
	{
		std::getline(file, line);
		std::stringstream sstream(line);

		while (sstream >> n_value)
		{
			if (n_value == FileSeparator)
			{
				continue;
			}

			colnames.push_back(n_value);
		}
	}

	return colnames;
}

std::vector<Edge> CsvGraphReader::CreateEdges(std::ifstream& file)
{
	std::vector<Edge> edges;
	std::vector<char> headers = GetFileHeaders(file);

	if (headers.size() == 0 || headers[0] == Connected || headers[0] == Empty)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			int c_value = StartingChar + i;

			std::string label = (c_value > EndingChar)
				? GenerateLabel(c_value)
				: std::string(1, c_value);

			Edge edge(label);
			edges.push_back(edge);
		}
	}
	else
	{
		for (char header : headers)
		{
			std::string label(1, header);
			Edge edge(label);

			edges.push_back(edge);
		}
	}

	return edges;
}

std::string CsvGraphReader::GenerateLabel(int value)
{
	int c_amount = ceil(value / EndingChar);
	int diff = EndingChar - value;

	std::string label;
	for (int i = 0; i < c_amount - 1; i++)
	{
		label.append(std::string(1, (char)StartingChar));
	}

	label.append(std::string(1, (char)diff));
	return label;
}