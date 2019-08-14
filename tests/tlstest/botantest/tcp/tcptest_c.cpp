// g++ tcptest_c.cpp my_tcp_channel.cpp my_tcp_setup.cpp -o tcptest_c -std=c++11
// ./tcptest.c CLIENT_PORT SERVER_PORT




#include "my_tcp_setup.h"
#include "my_tcp_channel.h"


int main(int argc, char** argv){

  if(argc != 3){
    return -1;
  }

  My_tcp_setup ms;
  if (0!=ms.set_my_sock(NULL, argv[1])){
    std::cout<<"set_my_sock\n";

  }



  int sock= ms.get_sock_by_connect("127.0.0.1", argv[2]);
  if(sock==-1){
    std::cout<<"get_sock_by_connect\n";
  }

  printf("out:%d\n",sock);

  My_tcp_channel my_channel(sock);

  char buff[] = "aaaaa";
  int len = my_channel.my_send(buff, 6);

  printf("%d\n",len);
  perror("send");





}
