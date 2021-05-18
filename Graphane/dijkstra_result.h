#pragma once
#include <string>
#include <vector>

using namespace std;

struct DijkstraResult
{
	string origin;
	string destination;
	vector<string> path;
	int weight;
};
