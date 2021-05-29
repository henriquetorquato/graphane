#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphaneTests
{
	TEST_CLASS(KosarajuTests)
	{
	private:
		void AssertResult(vector<string> expected, vector<string> actual)
		{
			Assert::AreEqual(
				ToString(expected, DEFAULT_LIST_SEPARATOR),
				ToString(actual, DEFAULT_LIST_SEPARATOR)
			);
		}

	public:
		TEST_METHOD(FindStronglyConnectedComponents_WithDirectionalGraph_ShouldFindEveryComponent)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalA());
			Kosaraju kosaraju(graph);

			// When: finding the strongly connected components
			vector<vector<string>> result = kosaraju.FindStronglyConnectedComponents();

			// Then: there should be 7 components
			Assert::AreEqual(size_t(7), result.size());

			// And: the components should be
			AssertResult({ "A" },           result.at(0));
			AssertResult({ "D", "H" },      result.at(1));
			AssertResult({ "E" },           result.at(2));
			AssertResult({ "B" },           result.at(3));
			AssertResult({ "C", "F", "J" }, result.at(4));
			AssertResult({ "I" },           result.at(5));
			AssertResult({ "G" },           result.at(6));
		}

		TEST_METHOD(FindStronglyConnectedComponents_WithBiDirectionalGraph_ShouldFindSingleComponent)
		{
			// Given: there is a bi-directional graph
			Graph graph(GraphGenerator::CreateBiDirectional());
			Kosaraju kosaraju(graph);

			// When: finding the strongly connected components
			vector<vector<string>> result = kosaraju.FindStronglyConnectedComponents();

			// Then: there should be a single component
			Assert::AreEqual(size_t(1), result.size());

			// And: the components should be
			AssertResult({ "A", "B", "E", "H", "D", "G", "F", "C", "J", "I" }, result.at(0));
		}
	};
}