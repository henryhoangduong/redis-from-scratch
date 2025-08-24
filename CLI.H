#ifndef CLI_H
#define CLI_H
#include "RedisClient.H"
#include <string>
class CLI {
public:
  CLI(const std::string &host, int port);
  void run();

private:
  RedisClient redisClient;
};
#endif