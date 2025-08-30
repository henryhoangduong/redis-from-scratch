#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <sstream>
#include <string>
#include <vector>

class CommandHandler {
public:
  static std::vector<std::string> splitArgs(const std::string &input);
  static std::string buildRESPcommand(const std::vector<std::string> &args);
};
#endif