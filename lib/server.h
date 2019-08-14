/*
* Filename: server.h
* Author: Zelin Liu
* Date: 2019/08/13
* Description: definition for Server
* Instruction:
*/
#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>

class Server{
public:
  Server(std::string hostname, std::string port, int num_thread, int socket_per_thread);
  int command(std::string cmd);
  ~Server();
private:
  int start();

  int launch_threads();

  void master_thread();
  void worker_thread();

  int shutdown();
  std::string hostname;
  std::string port;
  int num_thread;
  int socket_per_thread;
};
#endif
