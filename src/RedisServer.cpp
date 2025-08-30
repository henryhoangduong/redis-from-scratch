#include "../include/RedisServer.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
static RedisServer *globaServer = nullptr;

RedisServer::RedisServer(int port)
    : port(port), server_socket(-1), running(true) {
  globaServer = this;
}
void RedisServer::shutdown() {
  running = false;
  if (server_socket != -1) {
    close(server_socket);
  }
  std::cout << "Server shutdown completely " << std::endl;
}

void RedisServer::run() {
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    std::cerr << "Error creating server socket" << std::endl;
    return;
  }
  int opt = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(server_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) <
      0) {
    std::cerr << "Error binding server socket \n";
  }
  if (listen(server_socket, 10) < 0) {
    std::cerr << "Error listening on server socket.\n";
    return;
  }
  std::cout << "Redis Server listening on port " << port << endl;
}