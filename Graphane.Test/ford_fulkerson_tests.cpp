#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphaneTests
{
	TEST_CLASS(FordFulkersonTests)
	{
	public:
		TEST_METHOD(FindMaximumFlow_WithDirectionalGraph_ShouldSucceed)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalB());
			FordFulkerson ford_fulkerson(graph);

			// When: calculating the maximum flow from S to T
			int result = ford_fulkerson.FindMaximumFlow("S", "T");

			// Then: the maximum flow should always be 19
			Assert::AreEqual(19, result);
		}

		TEST_METHOD(IsGraphValid_WithDirectionalGraph_ShouldReturnTrue)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalB());

			// When: checking if the graph is valid
			bool result = FordFulkerson::IsGraphValid(graph, "S", "T");

			// Then: the result shoud be true
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(IsGraphValid_WithBidirectionalGraph_ShouldReturnFalse)
		{
			// Given: there is a bi-directional graph
			Graph graph(GraphGenerator::CreateBiDirectional());

			// When: checking if the graph is valid
			bool result = FordFulkerson::IsGraphValid(graph, "S", "T");

			// Then: the result shoud be true
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(IsGraphValid_WithInvalidSource_ShouldReturnFalse)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalB());

			// When: checking if the graph is valid
			bool result = FordFulkerson::IsGraphValid(graph, "A", "T");

			// Then: the result shoud be false
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(IsGraphValid_WithInvalidTerminal_ShouldReturnFalse)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalB());

			// When: checking if the graph is valid
			bool result = FordFulkerson::IsGraphValid(graph, "S", "A");

			// Then: the result shoud be false
			Assert::AreEqual(false, result);
		}
	};
}