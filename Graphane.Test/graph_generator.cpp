#include "pch.h"

using namespace std;

Graph GraphGenerator::CreateDirectionalA()
{
    GraphBuilder graph_builder;

    graph_builder.AddNodes(vector<string> {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" });

    graph_builder.AddEdge("0",  5, "A", "C", EdgeType::Directional);
    graph_builder.AddEdge("1",  4, "A", "D", EdgeType::Directional);

    graph_builder.AddEdge("2",  7, "B", "G", EdgeType::Directional);

    graph_builder.AddEdge("3",  3, "C", "F", EdgeType::Bidirectional);

    graph_builder.AddEdge("4",  3, "D", "B", EdgeType::Directional);
    graph_builder.AddEdge("5",  2, "D", "H", EdgeType::Bidirectional);

    graph_builder.AddEdge("6",  3, "E", "B", EdgeType::Directional);

    graph_builder.AddEdge("7",  2, "F", "J", EdgeType::Directional);

    graph_builder.AddEdge("8",  2, "H", "E", EdgeType::Directional);

    graph_builder.AddEdge("9",  3, "I", "G", EdgeType::Directional);

    graph_builder.AddEdge("10", 2, "J", "C", EdgeType::Directional);
    graph_builder.AddEdge("11", 1, "J", "I", EdgeType::Directional);

    return graph_builder.Build();
}

Graph GraphGenerator::CreateDirectionalB()
{
    GraphBuilder graph_builder;

    graph_builder.AddNodes(vector<string> { "S", "A", "B", "C", "D", "T" });

    graph_builder.AddEdge("0", 10, "S", "A", EdgeType::Directional);
    graph_builder.AddEdge("1", 10, "S", "C", EdgeType::Directional);

    graph_builder.AddEdge("2", 4,  "A", "B", EdgeType::Directional);
    graph_builder.AddEdge("3", 2,  "A", "C", EdgeType::Directional);
    graph_builder.AddEdge("4", 8,  "A", "D", EdgeType::Directional);

    graph_builder.AddEdge("5", 10, "B", "T", EdgeType::Directional);

    graph_builder.AddEdge("6", 9,  "C", "D", EdgeType::Directional);

    graph_builder.AddEdge("7", 6,  "D", "B", EdgeType::Directional);
    graph_builder.AddEdge("8", 10, "D", "T", EdgeType::Directional);

    return graph_builder.Build();
}

Graph GraphGenerator::CreateBiDirectional()
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