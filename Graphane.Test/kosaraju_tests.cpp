#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphaneTests
{
	TEST_CLASS(KosarajuTests)
	{
	private:
		void AssertResult(vector<string> expected, KosarajuComponents actual)
		{
			Assert::AreEqual(
				ToString(expected, DEFAULT_LIST_SEPARATOR),
				ToString(actual.nodes, DEFAULT_LIST_SEPARATOR)
			);
		}

	public:
		TEST_METHOD(FindStronglyConnectedComponents_WithDirectionalGraph_ShouldFindEveryComponent)
		{
			// Given: there is a directional graph
			Graph graph(GraphGenerator::CreateDirectionalA());
			Kosaraju kosaraju(graph);

			// When: finding the strongly connected components
			KosarajuResult result = kosaraju.FindStronglyConnectedComponents();

			// Then: there should be 7 components
			Assert::AreEqual(size_t(7), result.components.size());

			// And: the components should be
			AssertResult({ "A" },           result.components.at(0));
			AssertResult({ "D", "H" },      result.components.at(1));
			AssertResult({ "E" },           result.components.at(2));
			AssertResult({ "B" },           result.components.at(3));
			AssertResult({ "C", "F", "J" }, result.components.at(4));
			AssertResult({ "I" },           result.components.at(5));
			AssertResult({ "G" },           result.components.at(6));
		}

		TEST_METHOD(FindStronglyConnectedComponents_WithBiDirectionalGraph_ShouldFindSingleComponent)
		{
			// Given: there is a bi-directional graph
			Graph graph(GraphGenerator::CreateBiDirectional());
			Kosaraju kosaraju(graph);

			// When: finding the strongly connected components
			KosarajuResult result = kosaraju.FindStronglyConnectedComponents();

			// Then: there should be a single component
			Assert::AreEqual(size_t(1), result.components.size());

			// And: the components should be
			AssertResult({ "A", "B", "E", "H", "D", "G", "F", "C", "J", "I" }, result.components.at(0));
		}
	};
}