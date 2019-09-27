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
#include <memory>
#include <deque>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include "macro.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class Listener{
public:
  Listener(std::string h, std::string p);
  ~Listener();
  void exit();
  void connect();
  int get_listener_sock();
  void AcceptNewSocks(std::shared_ptr<std::deque<int>> t_queue);
private:

  std::string hostname;
  std::string port;
  int listener_sock;
  static bool set_sock_nonblocking(int t_sock, bool non_blocking);
};
#endif
