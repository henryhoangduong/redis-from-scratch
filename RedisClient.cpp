#include "RedisClient.H"

RedisClient::RedisClient(const std::string &host, int port)
    : host(host), port(port), sockfd(-1) {}
RedisClient::~RedisClient() { disconnect(); }