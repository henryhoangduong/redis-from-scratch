#include "ResponseParser.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
static bool readChar(int sockfd, char &c) {
  ssize_t r = recv(sockfd, &c, 1, 0);
  return r == 1;
}

static std::string readLine(int sockfd) {
  std::string line;
  char c;
  while (readChar(sockfd, c)) {
    if (c == '\r') {
      // expect '\n', read and break;
      readChar(sockfd, c);
      break;
    }
    line.push_back(c);
  }
  return line;
}

std::string ResponseParser::parseResponse(int sockfd) {
  char prefix;
  if (!readChar(sockfd, prefix)) {
    return ("(Error) No response or connection closed");
  }
  switch (prefix) {
  case '+':
    return parseSimpleString(sockfd);
  case '-':
    return parseSimpleError(sockfd);
  case ':':
    return parseInteger(sockfd);
  case '$':
    return parseBulkString(sockfd);
  case '*':
    return parseArray(sockfd);
  default:
    return "(Error) Unknown reply type.";
  }
}

// Function to read a line of text from the socket until it encounters a
// carriage return;
std::string ResponseParser::parseSimpleString(int sockfd) {
  return readLine(sockfd);
};
std::string ResponseParser::parseSimpleError(int sockfd) {};
std::string ResponseParser::parseInteger(int sockfd) {};
std::string ResponseParser::parseBulkString(int sockdf) {};
std::string ResponseParser::parseArray(int sockfd) {};