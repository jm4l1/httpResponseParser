#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"
#include "Parser.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

const std::string response1 = R"(HTTP/1.0 200 OK
cache-control: public
content-length: 0
content-type: image/svg+xml
date: Tue, 22 Jun 2021 22:24:42 GMT)";

const std::string response2 = R"(HTTP/1.1 302 Found
cache-control: public
Transfer-encoding: chunked
invalid_header
date: Tue, 22 Jun 2021 22:24:42 GMT)";

const std::string response3 = R"(Header1: value1
date: Tue, 22 Jun 2021 22:24:42 GMT
content-length: 1337)";

const std::string response4 = "HTTP/2.0 401 UNAUTHORIZED\r\nd@te: Tue, 22 Jun 2021 22:24:42 GMT\r\ncontent-length: 1337";
const std::string response5 = "";
const std::string response6 = "HTTP/2.0";
const std::string response7 = "HTTP/2.0 4 NOT_FOUND";
const std::string response8 = "HTTP/2.0 4 NOT_FOUND\ndate: Tue, 22 Jun 2021 22:24:42 GMT\ncontent-length: 1337";
const std::string response9 = "HTTP/2.0 404 NOT_FOUND";

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
	REQUIRE_NOTHROW(parser.parse(response4));
	REQUIRE(parser.number_of_valid_headers() == 1);
	REQUIRE(parser.number_of_invalid_headers() == 1);
	REQUIRE_THROWS(parser.parse(response5));
	REQUIRE_THROWS(parser.parse(response6));
	REQUIRE_THROWS(parser.parse(response7));
	REQUIRE_THROWS(parser.parse(response8));
	REQUIRE_NOTHROW(parser.parse(response9));
	REQUIRE(parser.number_of_valid_headers() == 0);
	REQUIRE(parser.number_of_invalid_headers() == 0);
}
