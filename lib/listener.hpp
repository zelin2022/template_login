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
#include <memory>
#include <deque>




class Listener{
public:
  Listener(std::string t_hostname, std::string t_port);
  ~Listener();
  void exit();
  void connect();
  int get_listener_sock();
  void AcceptNewSocks(std::shared_ptr<std::deque<int>> t_queue);
private:

  std::string m_hostname;
  std::string m_port;
  int m_listener_sock;
  static void print_addr(struct sockaddr_storage addr);
  static bool set_sock_nonblocking(int t_sock, bool non_blocking);
};
#endif
