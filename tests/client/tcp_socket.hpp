/*
* Filename: tcp_socket.hpp
* Author: Zelin Liu
* Date: 2019/09/30
* Description:
* Instruction:
*/
#ifndef _TCP_SOCKET_HPP_
#define _TCP_SOCKET_HPP_
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
class TCP_Socket
{
public:
  TCP_Socket(bool t_is_server, char* t_my_ip, char* t_my_port, char* t_their_ip, char* t_their_port);
  ssize_t read(char* t_buffer, ssize_t t_len);
  bool write(void *t_buffer, int t_len);
  void exit();
private:
  static int SocketSetup(char* t_my_ip, char* t_my_port);
  static int connect(int socket, char* t_their_ip, char* t_their_port);
  int m_socket;
  const bool m_is_server;

};
#endif
