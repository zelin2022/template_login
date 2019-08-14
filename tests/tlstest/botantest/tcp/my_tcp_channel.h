/*
* Filename: my_tcp_channel.h
* Author: Zelin Liu
* Date: 2019/07/28
* Description:
* Instruction:
*/
#ifndef MY_TCP_CHANNEL_H_
#define MY_TCP_CHANNEL_H_

#include <ctime>
// #include <poll.h>
// #include <cstring>
// #include <cstdio>
// #include <iostream>
#include <unistd.h>
// #include <thread>
// #include <atomic>
// #include <chrono>

#include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <netdb.h>

class My_tcp_channel{
private:
  int socket;
  std::time_t last_recv_time;
public:
  My_tcp_channel(int s);
  ssize_t my_send(char* buffer, size_t buffer_len);
  ssize_t my_recv(char* buffer, size_t buffer_len);
  int my_close();
};

#endif
