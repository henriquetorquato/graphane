#include "csv_graph_reader.h"
#include "node.h"
#include "graph.h"
#include <sstream>
#include <iostream>

const char FileSeparator = ';';
const std::string Empty = "0";
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
		std::vector<Node> nodes = CreateNodes(file);

		Graph graph;
		graph.AddNodes(nodes);

		char n_value;
		int line_index = 0;
		int edge_index = 0;
		std::string line;

		while (std::getline(file, line))
		{
			int col_index = 0;
			std::stringstream sstream(line), next_value;
			Node* node_a = graph.GetNodeAt(line_index);

			while (sstream >> n_value)
			{
				if (n_value != FileSeparator)
				{
					next_value << n_value;
					continue;
				}

				if (next_value.str() == Empty)
				{
					col_index++;
					next_value.str(std::string());

					continue;
				}

				Node* node_b = graph.GetNodeAt(col_index);

				std::string edge_label = std::to_string(edge_index);
				int edge_value = std::stoi(next_value.str());

				Edge edge(edge_label, edge_value, node_a, node_b);
				graph.AddEdge(edge);

				next_value.str(std::string());
				col_index++;
				edge_index++;
			}

			line_index++;
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

std::vector<std::string> CsvGraphReader::ReadHeader(std::ifstream &file)
{
	std::string line;
	std::vector<std::string> colnames;
	char n_value;

	if (file.good())
	{
		std::getline(file, line);
		std::stringstream sstream(line), next_value;

		while (sstream >> n_value)
		{
			if (n_value != FileSeparator)
			{
				next_value << n_value;
				continue;
			}

			colnames.push_back(next_value.str());
			next_value.str(std::string());
		}

		// Add last col
		colnames.push_back(next_value.str());
	}

	try 
	{
		// Header check
		std::stoi(colnames[0]);
		return std::vector<std::string>();
	}
	catch (std::invalid_argument)
	{
		// If breaks on str to int cast then there are headers
		return colnames;
	}
}

std::vector<Node> CsvGraphReader::CreateNodes(std::ifstream& file)
{
	std::vector<Node> nodes;
	std::vector<std::string> headers = ReadHeader(file);

	if (headers.size() == 0)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			int c_value = StartingChar + i;

			std::string label = (c_value > EndingChar)
				? GenerateLabel(c_value)
				: std::string(1, c_value);

			Node node(label);
			nodes.push_back(node);
		}
	}
	else
	{
		for (std::string label : headers)
		{
			Node node(label);
			nodes.push_back(node);
		}
	}

	return nodes;
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