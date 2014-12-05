// Copyright Robert Dickerson 2014


# <SDL_net.h>

# "include/networkmanager.h"

namespace Hodhr {


NetworkManager::NetworkManager() {
  if (SDLNet_Init() == -1) {
    fprintf(stderr, "Error initializing networking\n");
  }
}


NetworkManager::~NetworkManager() {
  fprintf(stderr, "Destroying Networking manager\n");
}

void NetworkManager::connectServer(std::string hostaddress, int port) {
  IPaddress ip;

  if (SDLNet_ResolveHost(&ip, hostaddress.c_str(), port) == -1) {

    fprintf(stderr, "Problem resolving host\n");
  }

  tcpsock = SDLNet_TCP_Open(&ip);
  if (!tcpsock) {
    fprintf(stderr, "Error opening SDL network");
    exit(2);
  }
}

void NetworkManager::disconnectServer() {
  fprintf(stderr, "Disconnected from server");
}

}  // namespace Hodhr
