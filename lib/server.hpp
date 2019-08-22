/*
* Filename: server.hpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: definition for Server
* Instruction:
*/
#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include "channel_master_slave.hpp"

class Server{
public:
  Server(std::string hostname, std::string port, int num_thread, int socket_per_thread);
  void give_command(std::string cmd);
  bool check_want_exit();
  ~Server();
private:
  void start();
  void exit();

  void create_thread_objs();
  void create_thread_handles();

  int create_listener_sock();





  std::vector<std::shared_ptr<Thread_slave>> v_slave_thread_object;
  std::unique_ptr<Thread_master> master_thread_object;

  std::vector<std::shared_ptr<Channel_master_slave>> p_channel_master_slave_list;

  std::thread thread_master_handle;
  std::vector<std::thread> thread_slave_handle_list;

  int listener_sock;
  bool want_exit;
  std::string hostname;
  std::string port;
  int num_thread;
  int socket_per_thread;
};
#endif
