#include "CLI.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string host = "127.0.0.1";
  int port = 6379;
  int i = 1;
  std::vector<std::string> commandArgs;
  while (i < argc) {
    std::string arg = argv[i];
    if (arg == "-h" && i + 1 < argc) {
      host = argv[++i];
    } else if (arg == "-p" && i + 1 < argc) {
      port = std::stoi(argv[++i]);
    } else {
      // Remaining args
      while (i < argc) {
        commandArgs.push_back(argv[i]);
        i++;
      }
      break;
    }
    ++i;
  }
  // Handle REPL command and one-shot command modes
  CLI cli(host, port);
  if (!commandArgs.empty()) {
    cli.executeCommand(commandArgs); // Execute command immediately
  } else {
    cli.run(); // launch REPL mode
  }
}