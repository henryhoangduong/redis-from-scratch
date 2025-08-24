#include "CLI.H"

CLI::CLI(const std::string &host, int port) : redisClient(host, port) {}