#include "pch.h"
#include "graph_utils.h"

using namespace std;

void CreateEdge(Graph& graph, string label, int weight, string node_a, string node_b, EdgeType type)
{
    optional<int> index_a = graph.FindNode(Node(node_a));
    optional<int> index_b = graph.FindNode(Node(node_b));

    Node* a = graph.GetNodeAt(index_a.value());
    Node* b = graph.GetNodeAt(index_b.value());

    graph.AddEdge(Edge(label, weight, a, b, type));
}

Graph GraphUtils::CreateGraph()
{
    Graph graph;

    graph.AddNodes(vector<Node> {
        Node("A"),
        Node("B"),
        Node("C"),
        Node("D"),
        Node("E"),
        Node("F"),
        Node("G"),
        Node("H"),
        Node("I"),
        Node("J"),
    });

    CreateEdge(graph, "0", 2, "A", "B", EdgeType::Bidirectional);
    CreateEdge(graph, "1", 5, "A", "C", EdgeType::Bidirectional);
    CreateEdge(graph, "2", 4, "A", "D", EdgeType::Bidirectional);

    CreateEdge(graph, "3", 3, "B", "E", EdgeType::Bidirectional);
    CreateEdge(graph, "4", 7, "B", "G", EdgeType::Bidirectional);

    CreateEdge(graph, "5", 3, "C", "F", EdgeType::Bidirectional);
    CreateEdge(graph, "6", 2, "C", "J", EdgeType::Bidirectional);

    CreateEdge(graph, "7", 2, "D", "H", EdgeType::Bidirectional);

    CreateEdge(graph, "8", 2, "E", "H", EdgeType::Bidirectional);

    CreateEdge(graph, "9", 1, "F", "G", EdgeType::Bidirectional);
    CreateEdge(graph, "10", 2, "F", "I", EdgeType::Bidirectional);

    CreateEdge(graph, "11", 1, "I", "J", EdgeType::Bidirectional);

    return graph;
}
