/*
* Filename: tlstest.cpp
* Author: Zelin Liu
* Date: 2019/07/22
* Description: main file for for a UDP client used to talk to UDP server
* Instruction: compile with g++ clienttest.cpp UDP_Client.cpp -o client_test
*/

#include "botan_tls_class.h"

int main(int argc, char** argv)
{
  // prepare all the parameters
  Callbacks callbacks;
  Botan::AutoSeeded_RNG rng;
  Botan::TLS::Session_Manager_In_Memory session_mgr(rng);
  Server_Credentials creds;
  Botan::TLS::Strict_Policy policy;

  // accept tls connection from client
  Botan::TLS::Server server(callbacks,
                            session_mgr,
                            creds,
                            policy,
                            rng);


  std::cout<< "server \n";

  // read data received from the tls client, e.g., using BSD sockets or boost asio
  // and pass it to server.received_data().
  // ...

  // send data to the tls client using server.send_data()
  // ...
}
