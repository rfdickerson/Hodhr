#include <iostream>

#include "SDL_net.h"

#include "networkmanager.h"

namespace Hodhr {


NetworkManager::NetworkManager()
{
  if (SDLNet_Init() == -1) {
    std::cout << "Error initializing networking" << std::endl;
  }
}


NetworkManager::~NetworkManager()
{
  std::cout << "Shutting down network manager" << std::endl;
}

void NetworkManager::connectServer(std::string hostaddress, int port)
{
  IPaddress ip;

  if (SDLNet_ResolveHost(&ip, hostaddress.c_str(), port) == -1) {
    std::cout << "Problem resolving host" << std::endl;
  }

  tcpsock = SDLNet_TCP_Open(&ip);
  if (!tcpsock) {
    std::cout << "Error opening sdl network" << std::endl;
    //std::cout << "SDLNet TCP Open: " << SDLNet_GetError() << std::endl;
    exit(2);
}
}

void NetworkManager::disconnectServer()
{
  
}

}
