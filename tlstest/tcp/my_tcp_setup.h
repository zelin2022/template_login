/*
* Filename: my_tcp_setup.cpp
* Author: Zelin Liu
* Date: 2019/07/28
* Description: This class takes ip and port, and returns some socket for communication, use My_tcp_channel for communication
* Instruction:
*/
#ifndef _MYTCP_H_
#define _MYTCP_H_



class My_tcp_setup{
private:
  int mysock;
  bool is_listening;


public:
  My_tcp_setup();
  int set_my_sock(char* ip, char* port);
  int get_sock_by_connect(char * ip, char * port);
  int listen();
  int get_sock_by_accept();
};

#endif
