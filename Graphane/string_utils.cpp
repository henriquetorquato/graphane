#include <string>
#include <vector>
#include <sstream>

std::string ToString(std::vector<std::string> items, std::string separator)
{
	int index = 0;
	std::stringstream s_stream;
	std::vector<std::string>::iterator item_i;

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