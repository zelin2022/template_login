/*
* Filename: my_tcp_setup.cpp
* Author: Zelin Liu
* Date: 2019/07/28
* Description: This class takes ip and port, and returns some socket for communication, use My_tcp_channel for communication
* Instruction:
*/
#ifndef _MYTCP_H_
#define _MYTCP_H_

// #include <poll.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <unistd.h>
// #include <thread>
// #include <atomic>
// #include <chrono>

// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <netdb.h>

class My_tcp_setup{
private:
  int mysock;
  bool is_listening;


public:
  My_tcp_setup();
  int set_my_sock(const char* ip, const char* port);
  int get_sock_by_connect(const char * ip, const char * port);
  int my_listen();
  int get_sock_by_accept(sockaddr* their_addr, socklen_t* sin_size);
};

#endif
