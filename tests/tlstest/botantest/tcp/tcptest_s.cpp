
// g++ tcptest_s.cpp my_tcp_channel.cpp my_tcp_setup.cpp -o tcptest_s -std=c++11
// ./tcptest_s SERVER_PORT



#include "my_tcp_setup.h"
#include "my_tcp_channel.h"

int main(int argc, char** argv){

  if (argc != 2){
    return -1;
  }

  My_tcp_setup ms;
  if (0!=ms.set_my_sock(NULL, argv[1])){
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

  My_tcp_channel my_channel(sock);
  char *buffer = (char*)malloc(100*sizeof(char));
  int len =0;


  my_channel.my_recv(buffer, 100);
  printf("len:%d\n",len);
  printf("msg::%s\n", buffer);




}
