/*
* Filename: tlstest.cpp
* Author: Zelin Liu
* Date: 2019/07/22
* Description: main file for for a UDP client used to talk to UDP server
* Instruction: compile with g++ tlstest_client.cpp tcp/my_tcp_setup.cpp -I /usr/local/include/botan-2 -std=c++17 -lbotan-2 -o test_client
*/

#include "botan_tls_class.h"
#include "tcp/my_tcp_setup.h"

int main(int argc, char** argv)
{


  My_tcp_setup ms;
  if (0!=ms.set_my_sock(NULL, "7999")){
    std::cout<<"set_my_sock\n";

  }



  int sock= ms.get_sock_by_connect("127.0.0.1", "8000");
  if(sock==-1){
    std::cout<<"get_sock_by_connect\n";
  }





  // prepare all the parameters
  Callbacks callbacks;
  callbacks.set_socket(sock);
  Botan::AutoSeeded_RNG rng;
  Botan::TLS::Session_Manager_In_Memory session_mgr(rng);
  Client_Credentials creds;
  // Server_Credentials creds;
  // Botan::TLS::Strict_Policy policy;
  // Botan::TLS::BSI_TR_02102_2 policy;
  My_Test_Policy policy;
  std::cout<<policy.to_string()<<std::endl;

  // open the tls connection
  Botan::TLS::Client client(callbacks,
    session_mgr,
    creds,
    policy,
    rng,
    Botan::TLS::Server_Information("127.0.0.1", 8000),
    Botan::TLS::Protocol_Version::TLS_V12);


    // client.renegotiate(true);
    // char buff[] = "123";
    // client.send((const uint8_t*)buff, 4);

    char buffer [10000];
    int test_list[5];
    test_list[0]=100;
    test_list[1]=1169;
    test_list[2]=530;
    int a =0;
    while(!client.is_closed())
    {
      ssize_t rec_len = recv(sock,buffer, test_list[a++], 0);

      printf("received: %d\n", rec_len);

      client.received_data((const uint8_t * )buffer, rec_len);
      // printf("up");
      // read data received from the tls server, e.g., using BSD sockets or boost asio
      // ...

      // send data to the tls server using client.send_data()


      // if(client.is_active()){
      //   printf("xxxxxx\n");
      // }

      if(client.is_active()){
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        char buffer[15];
        strcpy(buffer,"HelloWorld");
        client.send((const uint8_t * )buffer,11);
      }



    }
  }
