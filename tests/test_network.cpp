// Copyright Robert Dickerson 2014

#include <memory>
#include <utility>

#include "include/networkmanager.h"

int main(int argc, char** argv)  {
  fprintf(stdout, "Testing the network manager\n");

  auto networkMgr = std::make_unique<Hodhr::NetworkManager>();

  networkMgr->connectServer("localhost", 1337);

  return 0;
}
