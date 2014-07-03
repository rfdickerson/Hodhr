#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>

#include "SDL_net.h"

class NetworkManager
{
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


#endif
