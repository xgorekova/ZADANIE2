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

	for (const char *ptrA = a.c_str(), *ptrB = b.c_str(); ; ++ptrA, ++ptrB) 
	{

		if (*ptrA != *ptrB || !*ptrA || !*ptrB) return *ptrA < *ptrB;

	}

	return false;
}


bool EqualCaseInsensitive(const std::string& a, const std::string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}



bool LessCaseInsensitive(const std::string& a, const std::string& b)
{

	for (const char *ptrA = a.c_str(), *ptrB = b.c_str();; ++ptrA, ++ptrB)
	{
		if (tolower(*ptrA) != tolower(*ptrB) || !tolower(*ptrA) || !tolower(*ptrB)) 
			return tolower(*ptrA) < tolower(*ptrB); 

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


	if (filter == Filter::whitespacelines)
	{
		//lines.erase(std::remove(lines.begin(), lines.end(), '\n'), lines.end());
		for (std::vector<std::string>::iterator i = lines.begin(); i != lines.end();) 
		{
			bool white = true;
			for (int j = 0; j < (*i).length(); j++) 
			{
				char c = (*i)[j];
				if (!std::isspace(c)) white = false;
			}
			if (white) i = lines.erase(i);
			else ++i;
		}
	}


	if (order == Order::descending) {
		if (ignorovat)
			std::sort(lines.begin(), lines.end(), LessCaseInsensitive);
		else
			std::sort(lines.begin(), lines.end(), LessCaseSensitive); 

		std::reverse(lines.begin(), lines.end());
	}
	else 
	{
		if (ignorovat)
		{
				std::sort(lines.begin(), lines.end(), LessCaseInsensitive);
		}
		else
			std::sort(lines.begin(), lines.end(),LessCaseSensitive); 
	}

	if (filter == Filter::unique) {
		if(ignorovat)
			lines.erase(std::unique(lines.begin(), lines.end(), EqualCaseInsensitive),lines.end());
		else
			lines.erase(std::unique(lines.begin(), lines.end()), lines.end());

	}

	for (int i = 0; i < lines.size(); i++) {
		output << lines[i] << std::endl;
	}
	
	return true;
}