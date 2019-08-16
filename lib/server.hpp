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

class Server{
public:
  Server(std::string hostname, std::string port, int num_thread, int socket_per_thread);
  int give_command(std::string cmd);
  bool check_want_exit();
  ~Server();
private:
  int start();
  int exit();

  int create_thread_objs();
  int create_thread_handles();

  std::vector<std::shared<Thread_slave>> v_slave_thread_object;
  std::unique_ptr<Thread_master> master_thread_object;

  std::vector<std::shared_ptr<Shared_queue<int>>> p_shared_queue_list;
  std::vector<std::shared_ptr<int>> p_session_count_list;

  std::thread thread_master_handle;
  std::vector<std::thread> thread_slave_handle_list;

  bool want_exit;
  std::string hostname;
  std::string port;
  int num_thread;
  int socket_per_thread;
};
#endif
