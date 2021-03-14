#include "csv_graph_reader.h"
#include <iostream>

int main()
{
    CsvGraphReader reader("D:\\repos\\graphane\\Debug\\n3e2.csv");
    Graph graph = reader.ReadGraph();
}