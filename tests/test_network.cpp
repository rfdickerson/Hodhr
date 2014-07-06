#include <iostream>
#include <memory>
#include <utility>

#include "networkmanager.h"

using namespace std;

int main(int argc, char** argv) 
{
  cout << "Testing the network library" << endl;

  auto networkMgr = make_unique<Hodhr::NetworkManager>();

  networkMgr->connectServer("localhost", 1337);

  return 0;

}
