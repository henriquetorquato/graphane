#include "pch.h"
#include "graph_generator.h"

using namespace std;

static Graph CreateDirectionalGraph()
{
    GraphBuilder graph_builder;

    graph_builder.AddNodes(vector<string> {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" });

    graph_builder.AddEdge("0", 2, "A", "B", EdgeType::Directional);
    graph_builder.AddEdge("1", 5, "A", "C", EdgeType::Directional);
    graph_builder.AddEdge("2", 4, "A", "D", EdgeType::Directional);

    graph_builder.AddEdge("3", 3, "B", "E", EdgeType::Directional);
    graph_builder.AddEdge("4", 7, "B", "G", EdgeType::Directional);

    graph_builder.AddEdge("5", 3, "C", "F", EdgeType::Directional);
    graph_builder.AddEdge("6", 2, "C", "J", EdgeType::Directional);

    graph_builder.AddEdge("7", 2, "D", "H", EdgeType::Directional);

    graph_builder.AddEdge("8", 2, "E", "H", EdgeType::Directional);

    graph_builder.AddEdge("9", 1, "F", "G", EdgeType::Directional);
    graph_builder.AddEdge("10", 2, "F", "I", EdgeType::Directional);

    graph_builder.AddEdge("11", 1, "I", "J", EdgeType::Directional);

    return graph_builder.Build();
}

static Graph CreateBidirectionalGraph()
{
    GraphBuilder graph_builder;

    graph_builder.AddNodes(vector<string> {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" });

    graph_builder.AddEdge("0", 2, "A", "B", EdgeType::Bidirectional);
    graph_builder.AddEdge("1", 5, "A", "C", EdgeType::Bidirectional);
    graph_builder.AddEdge("2", 4, "A", "D", EdgeType::Bidirectional);

    graph_builder.AddEdge("3", 3, "B", "E", EdgeType::Bidirectional);
    graph_builder.AddEdge("4", 7, "B", "G", EdgeType::Bidirectional);

    graph_builder.AddEdge("5", 3, "C", "F", EdgeType::Bidirectional);
    graph_builder.AddEdge("6", 2, "C", "J", EdgeType::Bidirectional);

    graph_builder.AddEdge("7", 2, "D", "H", EdgeType::Bidirectional);

    graph_builder.AddEdge("8", 2, "E", "H", EdgeType::Bidirectional);

    graph_builder.AddEdge("9", 1, "F", "G", EdgeType::Bidirectional);
    graph_builder.AddEdge("10", 2, "F", "I", EdgeType::Bidirectional);

    graph_builder.AddEdge("11", 1, "I", "J", EdgeType::Bidirectional);

    return graph_builder.Build();
}

Graph GraphGenerator::Create(bool directional)
{
    return directional
        ? CreateDirectionalGraph()
        : CreateBidirectionalGraph();
}