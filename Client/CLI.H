#ifndef CLI_H
#define CLI_H
#include "CommandHandler.h"
#include "RedisClient.h"
#include "ResponseParser.h"
#include <string>
class CLI {
public:
  CLI(const std::string &host, int port);
  void run();
  void executeCommand(const std::vector<std::string> &args);

private:
  std::string host;
  int port;
  RedisClient redisClient;
};
#endif