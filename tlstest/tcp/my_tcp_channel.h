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

class My_tcp_channel{
private:
  int socket;
  std::time_t last_recv_time;
public:
  My_tcp_channel(int s);
  ~My_tcp_channel();
  int send();
  int recv();
  int close();
};

#endif
