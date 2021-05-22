#include "pch.h"
#include "CppUnitTest.h"
#include "graph_generator.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphaneTests
{
	TEST_CLASS(DijkstraTests)
	{
	private:
		tuple<int, vector<string>> GetResult(string origin, string destination, vector<DijkstraResult> results)
		{
			vector<DijkstraResult>::iterator result_i;
			for (result_i = results.begin(); result_i != results.end(); result_i++)
			{
				DijkstraResult result(*result_i);
				if (result.origin == origin && result.destination == destination)
				{
					return { result.weight, result.path };
				}
			}

			return { -1, vector<string>() };
		}

		void AssertResult(int expected_weight, vector<string> expected_path, tuple<int, vector<string>> result)
		{
			int result_weight;
			vector<string> result_path;

			tie(result_weight, result_path) = result;

			Assert::AreEqual(expected_weight, result_weight);

			Assert::AreEqual(
				ToString(expected_path, DEFAULT_LIST_SEPARATOR),
				ToString(result_path, DEFAULT_LIST_SEPARATOR)
			);
		}

	public:
		TEST_METHOD(FindShortestPath_WithoutDestination_ShouldFindEveryPath)
		{
			// Given: there is a graph
			Graph graph(GraphGenerator::Create());
			Dijkstra dijkstra(graph);

			// When: finding the shortest path from `G`
			vector<DijkstraResult> result = dijkstra.FindShortestPath("G");

			// Then: there should be 9 paths
			Assert::AreEqual(size_t(9), result.size());

			// And: the paths should be
			AssertResult(1,  { "G", "F" },                GetResult("G", "F", result));
			AssertResult(3,  { "G", "F", "I" },           GetResult("G", "I", result));
			AssertResult(4,  { "G", "F", "C" },           GetResult("G", "C", result));
			AssertResult(4,  { "G", "F", "I", "J" },      GetResult("G", "J", result));
			AssertResult(7,  { "G", "B" },                GetResult("G", "B", result));
			AssertResult(9,  { "G", "F", "C", "A" },      GetResult("G", "A", result));
			AssertResult(10, { "G", "B", "E" },           GetResult("G", "E", result));
			AssertResult(12, { "G", "B", "E", "H" },      GetResult("G", "H", result));
			AssertResult(13, { "G", "F", "C", "A", "D" }, GetResult("G", "D", result));
		}

		TEST_METHOD(FindShortestPath_WithDestination_ShouldFindPath)
		{
			// Given: there is a graph
			Graph graph(GraphGenerator::Create());
			Dijkstra dijkstra(graph);

			// When: finding the shortest path from `G` to `J`
			vector<DijkstraResult> result = dijkstra.FindShortestPath("G", "J");

			// Then: there should be one path
			Assert::AreEqual(size_t(1), result.size());

			// And: the paths should be
			AssertResult(4, { "G", "F", "I", "J" }, GetResult("G", "J", result));
		}
	};
}