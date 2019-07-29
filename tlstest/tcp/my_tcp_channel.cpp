/*
* Filename: my_tcp_channel.cpp
* Author: Zelin Liu
* Date: 2019/07/28
* Description: method implementation for My_tcp_channel class
* Instruction:
*/


#include "my_tcp_channel.h"

My_tcp_channel::My_tcp_channel(int s){}
ssize_t My_tcp_channel::send(char* buffer, size_t buffer_len){
  if(this->socket <= 0){
    return -1;
  }
  return send(this->socket, buffer, buffer_len, 0);
}

ssize_t My_tcp_channel::recv(char* buffer, size_t buffer_len){
  // on success, refresh last_recv_time
  if(this->socket <= 0 ){
    return -1;
  }

  ssize_t rv = 0;
  rv = recv(this->socket, buffer, buffer_len, 0);
  if(rv > 0){
    this->last_recv_time = std::time(nullptr);
  }
  return rv
}

int My_tcp_channel::close(){
  if(this->socket == -1){
    return -1;
  }
  close(this->socket);
  this->socket = -1;
  return 0;
}
