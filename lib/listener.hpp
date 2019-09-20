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
#include <vector>

class Listener{
public:
  Listener(std::string h, std::string p);
  ~Listener();
  void exit();
  void connect();
  int get_listener_sock();
  std::vector<int> get_accept_socks();
private:

  std::string hostname;
  std::string port;
  int listener_sock;
  bool set_sock_nonblocking(bool non_blocking);
};
#endif
