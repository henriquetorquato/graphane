#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int FIXED_SEED = 42;

namespace GraphaneTests
{
	TEST_CLASS(PrimTests)
	{
	private:
		void AssertResult(PrimPath expected_result, PrimPath actual_result)
		{
			Assert::AreEqual(expected_result.edge, actual_result.edge);
			Assert::AreEqual(expected_result.origin, actual_result.origin);
			Assert::AreEqual(expected_result.destination, actual_result.destination);
		}

	public:
		TEST_METHOD(FindMinimumSpanningTree_WithSeed_ShouldAlwaysFindTheSameMinimumSpanningTree)
		{
			// Given: there is a graph
			Graph graph(GraphGenerator::CreateBiDirectional());
			Prim prim(graph, FIXED_SEED);

			// When: finding the minimum spanning tree
			PrimResult minimum_tree = prim.FindMinimumSpanningTree();

			// Then: the tree should have 10 edges
			Assert::AreEqual(size_t(10), minimum_tree.paths.size());

			// And: the edges should be
			AssertResult({ "F", "G", "9" },  minimum_tree.paths.at(0));
			AssertResult({ "F", "I", "10" }, minimum_tree.paths.at(1));
			AssertResult({ "I", "J", "11" }, minimum_tree.paths.at(2));
			AssertResult({ "J", "C", "6" },  minimum_tree.paths.at(3));
			AssertResult({ "F", "C", "5" },  minimum_tree.paths.at(4));
			AssertResult({ "C", "A", "1" },  minimum_tree.paths.at(5));
			AssertResult({ "A", "B", "0" },  minimum_tree.paths.at(6));
			AssertResult({ "B", "E", "3" },  minimum_tree.paths.at(7));
			AssertResult({ "E", "H", "8" },  minimum_tree.paths.at(8));
			AssertResult({ "H", "D", "7" },  minimum_tree.paths.at(9));
		}

		TEST_METHOD(FindMinimumSpanningTree_WithotSeed_ShouldFindTheSameMinimumSpanningTreeLength)
		{
			// Given: there is a graph
			Graph graph(GraphGenerator::CreateBiDirectional());
			Prim prim(graph);

			// When: finding the minimum spanning tree
			PrimResult minimum_tree = prim.FindMinimumSpanningTree();

			// Then: the tree should always have the same edges
			Assert::AreEqual(size_t(10), minimum_tree.paths.size());
		}

		TEST_METHOD(IsGraphValid_WithDirectionalGraph_ShouldReturnFalse)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalB());
			
			// When: checking if a graph is valid
			bool result = Prim::IsGraphValid(graph);

			// Then: the result should be false
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(IsGraphValid_WithBidirectionalGraph_ShouldReturnTrue)
		{
			// Given: there is a bidirectional graph
			Graph graph(GraphGenerator::CreateBiDirectional());

			// When: checking if a graph is valid
			bool result = Prim::IsGraphValid(graph);

			// Then: the result should be true
			Assert::AreEqual(true, result);
		}
	};
}