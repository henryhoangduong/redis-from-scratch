#include "CLI.h"
#include "CommandHandler.h"
#include "ResponseParser.h"
static std::string trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\n\r\f\v");
  if (start == std::string::npos)
    return "";
  size_t end = s.find_last_not_of(" \t\n\r\f\v");
  return s.substr(start, end - start + 1);
}

CLI::CLI(const std::string &host, int port)
    : host(host), port(port), redisClient(host, port) {}

void CLI::run() {
  if (!redisClient.connectToServer()) {
    return;
  }
  std::cout << "Connected to Redis at " << redisClient.getSocketFD() << "\n";
  std::string host = "127.0.0.1";
  int port = 6379;
  while (true) {
    std::cout << host << ": " << port << "> ";
    std::cout.flush();
    std::string line;
    if (!std::getline(std::cin, line))
      break;
    line = trim(line);
    if (line.empty())
      continue;
    if (line == "quit") {
      std::cout << "Goodbye.\n";
      break;
    }
    if (line == "help") {
      std::cout << "Displaying help\n";
      continue;
    }
    std::vector<std::string> args = CommandHandler::splitArgs(line);
    if (args.empty())
      continue;
    std::string command = CommandHandler::buildRESPcommand(args);
    if (!redisClient.sendCommand(command)) {
      std::cerr << "(Error) Failed to send command" << std::endl;
      break;
    }
    // parse and print response
    std::string response =
        ResponseParser::parseResponse(redisClient.getSocketFD());
    std::cout << response << "\n";
  }
  redisClient.disconnect();
}

void CLI::executeCommand(const std::vector<std::string> &args) {
  if (args.empty())
    return;
  std::string command = CommandHandler::buildRESPcommand(args);
  if (!redisClient.sendCommand(command)) {
    std::cerr << "(Error) Failed to send command.\n";
    return;
  }
  // parse and print response
  std::string response =
      ResponseParser::parseResponse(redisClient.getSocketFD());
  std::cout << response << '\n';
  
}
