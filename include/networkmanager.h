// Copyright Robert Dickerson 2014

#ifndef INCLUDE_NETWORKMANAGER_H_
#define INCLUDE_NETWORKMANAGER_H_

#include <SDL_net.h>
#include <string>

namespace Hodhr {


class NetworkManager {
 public:
  NetworkManager();
  virtual ~NetworkManager();

  void connectServer(std::string ipaddress, int port);
  void disconnectServer();

 private:
  // handle to the socket
  int sockfd;
  TCPsocket tcpsock;
};

}  // namespace Hodhr

#endif  // INCLUDE_NETWORKMANAGER_H_
