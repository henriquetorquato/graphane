#include "pch.h"

#include "pch.h"
#include "CppUnitTest.h"
#include "graph_utils.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int FIXED_SEED = 42;

namespace GraphaneTests
{
	TEST_CLASS(PrimTests)
	{
	private:
		void AssertResult(PrimResult expected_result, PrimResult actual_result)
		{
			Assert::AreEqual(expected_result.edge, actual_result.edge);
			Assert::AreEqual(expected_result.origin, actual_result.origin);
			Assert::AreEqual(expected_result.destination, actual_result.destination);
		}

	public:
		TEST_METHOD(FindMinimumSpanningTree_WithSeed_ShouldAlwaysFindTheSameMinimumSpanningTree)
		{
			// Given: there is a graph
			Graph graph(GraphUtils::CreateGraph());
			Prim prim(graph, FIXED_SEED);

			// When: finding the minimum spanning tree
			vector<PrimResult> minimumSpanningTree = prim.FindMinimumSpanningTree();

			// Then: the tree should have 10 edges
			Assert::AreEqual(size_t(10), minimumSpanningTree.size());

			// And: the edges should be
			AssertResult({ "F", "G", "9" },  minimumSpanningTree.at(0));
			AssertResult({ "F", "I", "10" }, minimumSpanningTree.at(1));
			AssertResult({ "I", "J", "11" }, minimumSpanningTree.at(2));
			AssertResult({ "J", "C", "6" },  minimumSpanningTree.at(3));
			AssertResult({ "F", "C", "5" },  minimumSpanningTree.at(4));
			AssertResult({ "C", "A", "1" },  minimumSpanningTree.at(5));
			AssertResult({ "A", "B", "0" },  minimumSpanningTree.at(6));
			AssertResult({ "B", "E", "3" },  minimumSpanningTree.at(7));
			AssertResult({ "E", "H", "8" },  minimumSpanningTree.at(8));
			AssertResult({ "H", "D", "7" },  minimumSpanningTree.at(9));
		}

		TEST_METHOD(FindMinimumSpanningTree_WithotSeed_ShouldFindTheSameMinimumSpanningTreeLength)
		{
			// Given: there is a graph
			Graph graph(GraphUtils::CreateGraph());
			Prim prim(graph);

			// When: finding the minimum spanning tree
			vector<PrimResult> minimumSpanningTree = prim.FindMinimumSpanningTree();

			// Then: the tree should always have the same edges
			Assert::AreEqual(size_t(10), minimumSpanningTree.size());
		}
	};
}