#pragma once
#include <vector>
#include <string>

using namespace std;

const string DEFAULT_LIST_SEPARATOR = ", ";

string ToString(vector<string> items, string separator);
int FindString(vector<string> items, string item);