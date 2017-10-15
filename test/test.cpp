#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "options.h"
#include "sort.h"

#include <sstream>

TEST_CASE("Options")
{
	SECTION("no options")
	{
		char * argv[] = { "line-sort" };
		REQUIRE(options::parse(1, argv) == std::make_tuple(Order::ascending, Filter::all, Case::sensitive, (char *) nullptr));
	}


	SECTION("reversed")
	{
		SECTION("reversed with file")
		{
			char * argv[] = { "line-sort", "-r","subor.txt" };
			auto options = options::parse(3, argv);
			//REQUIRE(options == true);
			REQUIRE(options.value() == std::make_tuple(Order::descending, Filter::all, Case::sensitive, argv[2]));

		}
		SECTION("reversed without file")
		{
			char * argv[] = { "line-sort", "-r" };
			auto options = options::parse(2, argv);
			//REQUIRE(options == true);
			REQUIRE(options.value() == std::make_tuple(Order::descending, Filter::all, Case::sensitive, (char *) nullptr));
		}
	}

	SECTION("unique")
	{
		SECTION("unique with file") 
		{
			char * argv[] = { "line-sort","-u","subor.txt" };
			auto options = options::parse(3, argv);
			//REQUIRE(options == true);
			REQUIRE(options.value() == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, argv[2]));
		}
		SECTION("unique without file")
		{
			char * argv[] = { "line-sort","-u" };
			auto options = options::parse(2, argv);
			//REQUIRE(options == true);
			REQUIRE(options.value() == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, (char *) nullptr));
		}
		
	}

	SECTION("ignore case")
	{
		SECTION("ignore case with file")
		{
			char * argv[] = { "line-sort","-i","subor.txt" };
			auto options = options::parse(3, argv);
			//REQUIRE(options == true);
			REQUIRE(options.value() == std::make_tuple(Order::ascending, Filter::all, Case::ignore, argv[2]));
		}

		SECTION("ignore case without file")
		{
			char * argv[] = { "line-sort","-i" };
			auto options = options::parse(2, argv);
			//REQUIRE(options == true);
			REQUIRE(options.value() == std::make_tuple(Order::ascending, Filter::all, Case::ignore, (char *) nullptr));
		}
	}

	SECTION("multiple")
	{

	}
}

namespace
{
	namespace data
	{
		std::istringstream empty { R"()" };
		std::istringstream one_char { R"( )" };
		std::istringstream one_line { R"(
)" };
		std::istringstream numbered { R"(1
3
9
4
5
2
)" };
	}
}

TEST_CASE("Sorting")
{
	SECTION("ascending")
	{
		std::ostringstream output {};

		REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::empty, output) == true);
		REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "1\n2\n3\n4\n5\n9\n");
	}

	SECTION("ascending - unique")
	{
	}

	SECTION("ascending - unique - ignore case")
	{
	}

	SECTION("descending")
	{
	}

	SECTION("descending - unique")
	{
	}

	SECTION("descending - unique - ignore case")
	{
	}
}

