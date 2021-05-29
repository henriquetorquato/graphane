#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphaneTests
{
	TEST_CLASS(DijkstraTests)
	{
	private:
		DijkstraShortestPath GetPath(string origin, string destination, DijkstraResult results)
		{
			vector<DijkstraShortestPath>::iterator path_i;
			for (path_i = results.paths.begin(); path_i != results.paths.end(); path_i++)
			{
				DijkstraShortestPath shortest_path(*path_i);
				if (shortest_path.origin == origin && shortest_path.destination == destination)
				{
					return shortest_path;
				}
			}

			return  { string(), string(), vector<string>(), -1 };
		}

		void AssertResult(int expected_weight, vector<string> expected_path, DijkstraShortestPath result)
		{
			Assert::AreEqual(expected_weight, result.weight);

			Assert::AreEqual(
				ToString(expected_path, DEFAULT_LIST_SEPARATOR),
				ToString(result.path, DEFAULT_LIST_SEPARATOR)
			);
		}

	public:
		TEST_METHOD(FindShortestPath_WithoutDestination_ShouldFindEveryPath)
		{
			// Given: there is a graph
			Graph graph(GraphGenerator::CreateBiDirectional());
			Dijkstra dijkstra(graph);

			// When: finding the shortest path from `G`
			DijkstraResult result = dijkstra.FindShortestPath("G");

			// Then: there should be 9 paths
			Assert::AreEqual(size_t(9), result.paths.size());

			// And: the paths should be
			AssertResult(1,  { "G", "F" },                GetPath("G", "F", result));
			AssertResult(3,  { "G", "F", "I" },           GetPath("G", "I", result));
			AssertResult(4,  { "G", "F", "C" },           GetPath("G", "C", result));
			AssertResult(4,  { "G", "F", "I", "J" },      GetPath("G", "J", result));
			AssertResult(7,  { "G", "B" },                GetPath("G", "B", result));
			AssertResult(9,  { "G", "F", "C", "A" },      GetPath("G", "A", result));
			AssertResult(10, { "G", "B", "E" },           GetPath("G", "E", result));
			AssertResult(12, { "G", "B", "E", "H" },      GetPath("G", "H", result));
			AssertResult(13, { "G", "F", "C", "A", "D" }, GetPath("G", "D", result));
		}

		TEST_METHOD(FindShortestPath_WithDestination_ShouldFindPath)
		{
			// Given: there is a graph
			Graph graph(GraphGenerator::CreateBiDirectional());
			Dijkstra dijkstra(graph);

			// When: finding the shortest path from `G` to `J`
			DijkstraResult result = dijkstra.FindShortestPath("G", "J");

			// Then: there should be one path
			Assert::AreEqual(size_t(1), result.paths.size());

			// And: the paths should be
			AssertResult(4, { "G", "F", "I", "J" }, GetPath("G", "J", result));
		}
	};
}