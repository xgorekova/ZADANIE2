#include "sort.h"

#include <string>
#include <iterator>
#include <vector>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>


namespace
{
	struct Line : public std::string {};

	std::istream & operator >> (std::istream & is, Line & line)
	{
		return std::getline(is, line);
	}
}

bool LessCaseSensitive(const std::string& a, const std::string& b)
{
	for (const char * ptrA = a.c_str(), const char * ptrB = b.c_str();; ++ptrA, ++ptrB)
	{
		if (*ptrA != *ptrB || !*ptrA || !*ptrB) return *ptrA < *ptrB;

	}
	return false;
}


bool LessCaseInsensitive(const std::string& a, const std::string& b)
{

	for (const char * ptrA = a.c_str(), const char * ptrB = b.c_str();; ++ptrA, ++ptrB)
	{
		if (*ptrA != *ptrB || !*ptrA || !*ptrB) return *ptrA < *ptrB; //

	}
	return false;
}


bool sort::process(Order order, Filter filter, Case compare, std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines{ std::istream_iterator<Line>(input), std::istream_iterator<Line>() };

	bool ignorovat = false;
	if (compare == Case::ignore)
	{
		ignorovat = true;
	}

	if (order == Order::descending) {
		if (ignorovat)
			std::sort(lines.begin(), lines.end(), LessCaseInsensitive);
		else
			std::sort(lines.begin(), lines.end());

		std::reverse(lines.begin(), lines.end());
	}
	else {
		if (ignorovat)
		{
				std::sort(lines.begin(), lines.end(), porovnaj);
		}
		else
			std::sort(lines.begin(), lines.end());
	}

	if (filter == Filter::unique) {
		
			lines.erase(std::unique(lines.begin(), lines.end()), lines.end());
	}

	for (int i = 0; i < lines.size(); i++) {
		output << lines[i] << std::endl;
	}
	
	return true;
}

