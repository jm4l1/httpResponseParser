#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>

namespace HTTP
{
	struct StatusLine
	{
		std::string version;
		std::string status_code;
		std::string reason_phrase;
		std::string string() const
		{
			return version + " " + status_code + " " + reason_phrase;
		}
	};
	struct Header
	{
		std::string name;
		std::string value;
		bool is_valid;
		std::string string() const
		{
			return name + ":" + value;
		}
	};

	class Parser
	{
	public:
		Parser() = default;
		void parse(const std::string& buffer);
		int number_of_valid_headers() const;
		int number_of_invalid_headers() const;
		void print(bool show_invalid = false) const;

	private:
		void flush();

	private:
		StatusLine status_line;
		std::vector<Header> valid_headers;
		std::vector<Header> invalid_headers;
	};
}  // namespace HTTP
#endif