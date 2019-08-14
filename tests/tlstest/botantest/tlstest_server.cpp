/*
* Filename: tlstest.cpp
* Author: Zelin Liu
* Date: 2019/07/22
* Description: main file for for a UDP client used to talk to UDP server
* Instruction: compile with g++ tlstest_server.cpp tcp/my_tcp_setup.cpp -I /usr/local/include/botan-2 -std=c++17 -lbotan-2 -o test_server
*/

#include "botan_tls_class.h"
#include "tcp/my_tcp_setup.h"

int main(int argc, char** argv)
{


  My_tcp_setup ms;
  if (0!=ms.set_my_sock(NULL, "8000")){
    std::cout<<"set_my_sock\n";

  }
  if (0!=ms.my_listen()){
    std::cout<<"my_listen\n";
  }

  struct sockaddr_storage target_addr;
  memset(&target_addr, 0, sizeof(sockaddr_storage));
  socklen_t target_addr_len = sizeof(target_addr);

  int sock= ms.get_sock_by_accept((struct sockaddr *)&target_addr, &target_addr_len);
  if(sock==-1){
    std::cout<<"get_sock_by_accept\n";
  }



  // prepare all the parameters
  Callbacks callbacks;
  callbacks.set_socket(sock);
  Botan::AutoSeeded_RNG rng;
  Botan::TLS::Session_Manager_In_Memory session_mgr(rng);
  Server_Credentials creds;
  // Botan::TLS::Strict_Policy policy;
  // Botan::TLS::BSI_TR_02102_2 policy;
  My_Test_Policy policy;

  std::cout<<policy.to_string()<<std::endl;


  // accept tls connection from client
  Botan::TLS::Server server(callbacks,
                            session_mgr,
                            creds,
                            policy,
                            rng);


  std::cout<< "server \n";

  char buffer[10000];
  while(true){
    ssize_t rec_len = recv(sock,buffer, 10000, 0);
    if (rec_len <= 0){break;}
    printf("received: %d\n", rec_len);
    
    server.received_data((const uint8_t * )buffer, rec_len);
  }

  // read data received from the tls client, e.g., using BSD sockets or boost asio
  // and pass it to server.received_data().
  // ...

  // send data to the tls client using server.send_data()
  // ...
}
