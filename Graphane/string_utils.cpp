#include <string>
#include <vector>
#include <sstream>

using namespace std;

string ToString(vector<string> items, string separator)
{
	int index = 0;
	stringstream s_stream;
	vector<string>::iterator item_i;

	for (item_i = items.begin(); item_i != items.end(); item_i++, index++)
	{
		if (index != 0)
		{
			s_stream << separator;
		}

		s_stream << *item_i;
	}

	return s_stream.str();
}

int FindString(vector<string> items, string item)
{
	int index = 0;
	vector<string>::iterator items_i;

	for (items_i = items.begin(); items_i != items.end(); items_i++)
	{
		if (item == *items_i)
		{
			return index;
		}

		index++;
	}

	return -1;
}