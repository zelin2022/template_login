/*
* Filename: server.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Server implementations
* Instruction:
*/

#include "server.hpp"


/*
* @param:hostname the ip address of server
* @param:port The port of the server
* @param:num_thread The number of thread to launch
* @param:socket_per_thread The number of sockets each thread supports
*/
Server::Server(std::string hostname, std::string port, int num_thread, int socket_per_thread)
{
  this->hostname = hostname;
  this->port = port;
  if(num_thread > SERVER_NUM_THREAD_MAX || num_thread < SERVER_NUM_THREAD_MIN){
    throw std::runtime_error("Server created with wrong num_thread value : " + std::to_string(num_thread));
  }
  if(socket_per_thread > SERVER_SOCKET_PER_THREAD_MAX || socket_per_thread < SERVER_SOCKET_PER_THREAD_MIN){
    throw std::runtime_error("Server created with wrong socket_per_thread value : " + std::to_string(socket_per_thread));
  }
  this->num_thread = num_thread;
  this->socket_per_thread = socket_per_thread;
}

/*
*
*/
int Server::give_command(std::string command)
{
  if(command.compare(0,5, "start") == 0)
  {

  }
}

/*
*
*/
bool Server::check_want_exit()
{
  return this->want_exit;
}

/*
*
*/
int Server::start()
{
  create_thread_objs();
  create_thread_handles();
}

/*
*
*/
int create_thread_objs()
{
  //
  this->master_thread_object = make_unique<Thread_master>(new Thread_master());

  for(int i = 0; i < this->num_thread; i++)
  {
    std::shared_ptr<Shared_queue<int>> shared_queue_tmp = make_shared<Shared_queue<int>>(new Shared_queue<int>());
    std::shared_ptr<int> session_count_temp = new int(0);

    std::unique_ptr<Thread_slave> slave_tmp = make_unique<Thread_slave>(new Thread_slave(shared_queue_tmp, session_count_temp, i));
    this->master_thread_object.add_queue_to_list(shared_queue_tmp);

    v_slave_thread_object.push_back(tmp);
    p_shared_queue_list.push_back(shared_queue_tmp);
    p_session_count_list.push_back(session_count_temp);
  }
}

/*
*
*/
int create_thread_handles()
{
  thread_master_handle = std::thread();
  for(int i = 0; i < this->num_thread; i++)
  {
    std::thread tmp();
    thread_slave_handle_list.push_back(tmp);
  }
}
