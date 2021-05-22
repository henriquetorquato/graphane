#include "pch.h"
#include "graph_generator.h"

using namespace std;

Graph GraphGenerator::Create()
{
    GraphBuilder graph_builder;

    graph_builder.AddNodes(vector<string> {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" });

    graph_builder.AddEdge("0" , 2, "A", "B");
    graph_builder.AddEdge("1" , 5, "A", "C");
    graph_builder.AddEdge("2" , 4, "A", "D");

    graph_builder.AddEdge("3" , 3, "B", "E");
    graph_builder.AddEdge("4" , 7, "B", "G");

    graph_builder.AddEdge("5" , 3, "C", "F");
    graph_builder.AddEdge("6" , 2, "C", "J");

    graph_builder.AddEdge("7" , 2, "D", "H");

    graph_builder.AddEdge("8" , 2, "E", "H");

    graph_builder.AddEdge("9" , 1, "F", "G");
    graph_builder.AddEdge("10", 2, "F", "I");

    graph_builder.AddEdge("11", 1, "I", "J");

    return graph_builder.Build();
}
