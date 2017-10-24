#include "options.h"
#include <iostream>
#include <string>
#include <fstream> 


std::optional<std::tuple<Order, Filter, Case, char *>> options::parse(int argc, char * argv[])
{
	Order order{ Order::ascending };
	Filter filter{ Filter::all };
	Case compare{ Case::sensitive };
	char * input{ nullptr };
	int RUI[3] = { 0,0,0 };
	int poc = 0;
	int iny = 0;

	if (argc == 1)
	{
		return std::make_tuple(order, filter, compare, input);
	}



	for (int i = 1; i < 4 && i < argc; i++)
	{

		if (argv[i] == std::string("-r"))
		{
			order = Order::descending;
			RUI[0] = 1;
			poc++;
		}
		else if (argv[i] == std::string("-u"))
		{
			filter = Filter::unique;
			RUI[1] = 1;
			poc++;
		}
		else if (argv[i] == std::string("-i"))
		{
			compare = Case::ignore;
			RUI[2] = 1;
			poc++;
		}
		else
			iny++;
	}

	if (argc - 1 == poc)
	{
		return std::make_tuple(order, filter, compare, input);
	}


	if (argc -1 == poc+1)
	{
		return std::make_tuple(order, filter, compare, argv[argc - 1]);

	}
	else
	{
		return {};
	}
}
