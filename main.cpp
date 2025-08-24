#include "CLI.H"
#include <iostream>
#include <string>
int main(int argc, char *argv[]) {
  std::string host = "127.0.0.1";
  int port = 6379;
  int i = 1;
  while (i < argc) {
    std::string arg = argv[i];
    if (arg == "-h" && i + 1 < argc) {
      host = argv[++i];
    } else if (arg == "-p" && i + 1 < argc) {
      port = std::stoi(argv[++i]);
    } else {
      break;
    }
    ++i;
  }
}