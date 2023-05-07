#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"
#include "Parser.h"

#include <filesystem>
#include <iostream>

static std::string response1 = R"(HTTP/1.0 200 OK
cache-control: public
content-length: 0
content-type: image/svg+xml
date: Tue, 22 Jun 2021 22:24:42 GMT)";

static std::string response2 = R"(HTTP/1.1 302 Found
cache-control: public
Transfer-encoding: chunked
invalid_header
date: Tue, 22 Jun 2021 22:24:42 GMT)";

static std::string response3 = R"(Header1: value1
date: Tue, 22 Jun 2021 22:24:42 GMT
content-length: 1337)";

HTTP::Parser parser;

TEST_CASE("Test Status Line Parsing")
{
	REQUIRE_NOTHROW(parser.parse(response1));
	REQUIRE(parser.number_of_valid_headers() == 4);
	REQUIRE(parser.number_of_invalid_headers() == 0);
	REQUIRE_NOTHROW(parser.parse(response2));
	REQUIRE(parser.number_of_valid_headers() == 3);
	REQUIRE(parser.number_of_invalid_headers() == 1);
	REQUIRE_THROWS(parser.parse(response3));

	if (std::filesystem::exists("../data.json"))
	{
		std::ifstream test_data("../data.json");
		std::string test_data_string;
		test_data >> test_data_string;
		std::cout << test_data_string;
	}
}
