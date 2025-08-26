#include "CommandHandler.h"
#include <regex>
#include <string>
std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {
  std::vector<std::string> tokens;
  std::regex rgx(R"((\"[ˆ\"]+\"|\S+))");
  auto words_begin = std::sregex_iterator(input.begin(), input.end(), rgx);
  auto words_end = std::sregex_iterator();
  for (auto it = words_begin; it != words_end; ++it) {
    std::string token = it->str();
    if (token.size() >= 2 && token.front() == '\"' && token.back() == '\"') {
      token = token.substr(1, token.size() - 2);
    }
    tokens.push_back(token);
  }
  return tokens;
}