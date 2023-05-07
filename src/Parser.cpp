#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
namespace HTTP
{
	namespace Private
	{
		StatusLine parse_status_line(const std::string& buffer)
		{
			std::istringstream status_line_stream(buffer);
			StatusLine status_line;
			status_line_stream >> status_line.version >> status_line.status_code >> status_line.reason_phrase;

			std::regex version_regex(R"(([Hh][Tt].[Pp])/(\d.\d))");
			std::smatch version_match;
			if (!std::regex_match(status_line.version, version_match, version_regex))
			{
				throw std::invalid_argument("Invalid status line");
			}

			if (status_line.status_code.size() != 3)
			{
				throw std::invalid_argument("Invalid status line");
			}
			try
			{
				std::stoi(status_line.status_code);
			}
			catch (...)
			{
				throw std::invalid_argument("Invalid status line");
			}
			return status_line;
		};

		Header parse_header(const std::string& buffer)
		{
			Header header;
			std::istringstream header_line_stream(buffer);
			std::getline(header_line_stream, header.name, ':');
			std::getline(header_line_stream, header.value);
			std::regex header_regex("[^A-Za-z0-9-]");
			std::smatch header_match;
			header.is_valid = header.name != "" && !std::regex_match(header.name, header_match, header_regex) && header.value != "";
			return header;
		};
	}  // namespace Private

	void Parser::parse(const std::string& buffer)
	{
		flush();
		auto request_stream = std::stringstream(buffer);
		std::string stream_line;
		std::getline(request_stream, stream_line);

		// status line
		status_line = Private::parse_status_line(stream_line);
		// headers
		while (std::getline(request_stream, stream_line) && (stream_line != ""))
		{
			Header header = Private::parse_header(stream_line);
			if (header.is_valid)
			{
				valid_headers.emplace_back(header);
			}
			else
			{
				invalid_headers.emplace_back(header);
			}
		}
	};
	int Parser::number_of_valid_headers() const
	{
		return valid_headers.size();
	};
	int Parser::number_of_invalid_headers() const
	{
		return invalid_headers.size();
	};
	void Parser::print(bool show_invalid) const
	{
		std::cout << status_line.string() << "\n";
		std::for_each(valid_headers.begin(),
					  valid_headers.end(),
					  [](const auto& header)
					  {
						  std::cout << header.string() << "\n";
					  });
		if (show_invalid)
		{
			std::for_each(invalid_headers.begin(),
						  invalid_headers.end(),
						  [](const auto& header)
						  {
							  std::cout << header.string() << "\n";
						  });
		}
	}

	void Parser::flush()
	{
		valid_headers.clear();
		invalid_headers.clear();
	}
}  // namespace HTTP
