/*
* Filename: mytcp.cpp
* Author: Zelin Liu
* Date: 2019/07/28
* Description:
* Instruction:
*/
#ifndef _MYTCP_H_
#define _MYTCP_H_



class Mytcp{
private:
  int mysock;
  bool is_listening;


public:
  Mytcp();
  int set_my_sock(char* ip, char* port);
  int get_sock_by_connect(char * ip, char * port);
  int listen();
  int get_sock_by_accept();
};

#endif
