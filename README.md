# HTTP Response Parser

This is a basic implementation of an Hypertext Transfer Protocol (HTTP) parser. The parse is built with based on the following requirements.

> Each line in the HTTP response should be terminated with a CR LF sequence
○ The HTTP response will begin with a status line, followed by zero or more header
lines
○ A status line consists of the HTTP version, status code, and reason phrase, each
separated by a space
■ The HTTP version is the case-sensitive string “HTTP/” followed by a
major and minor version (e.g. HTTP/1.1)
■ The status code is a 3 digit numeric code
■ The reason phrase is a string describing the status code
○ A header line consists of a header name, followed by “: “, followed by the header
value
■ A header name can contain any letter, digit, and the character “-”
■ A header value can contain any visible/printable ASCII character

## Supported Operated Systems
Currently supports building on Linux and MacOs.

## Build Instructions
1. Clone this repo.
2. run the command`./build_install.sh`

## Run tests
- `./bin/tests`

## Run parser
- `./bin/httpResponseParser`