// not used
/*
* Filename: listener.hpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Listener definition
* Instruction:
*/
#ifndef _LISTENER_HPP_
#define _LISTENER_HPP_

#include <string>

class Listener{
public:
  Listener(std::string hostname, std::string port);
  int init();
  static bool set_sock_nonblocking(int sock, bool non_blocking);
  int start_listen();
  int get_connection(struct sockaddr& their_addr, socklen_t& sin_size);

private:
  std::string hostname;
  std::string port;
  int mysock;
  bool is_listening;


};
#endif
