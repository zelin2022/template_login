/*
* Filename: server.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Server implementations
* Instruction:
*/

#include "server.hpp"


/*
* Constructor for SERVER
*/
Server::Server(std::string hostname, std::string port, int num_thread, int socket_per_thread)
{
  this->hostname = hostname;
  this->port = port;

  // boundary check given values with macros defined in macro.h
  if(num_thread > SERVER_NUM_THREAD_MAX || num_thread < SERVER_NUM_THREAD_MIN){
    throw std::runtime_error("Server created with wrong num_thread value : " + std::to_string(num_thread));
  }
  if(socket_per_thread > SERVER_SOCKET_PER_THREAD_MAX || socket_per_thread < SERVER_SOCKET_PER_THREAD_MIN){
    throw std::runtime_error("Server created with wrong socket_per_thread value : " + std::to_string(socket_per_thread));
  }

  this->num_thread = num_thread;
  this->socket_per_thread = max_socket_per_thread;
  this->listener_sock = -1;

  v_slave_thread_object.reserve(num_thread);
  p_channel_master_slave_list.reserve(num_thread);
  p_session_count_list.reserve(num_thread); //
  thread_slave_handle_list.reserve(num_thread);
}

/*
* do something for cetain commands:
* ____
*/
void Server::give_command(std::string command)
{
  if(command.compare(0,5, "start") == 0)
  {

  }else if()
  {

  }
}

/*
* returns the bool value of a flag
* whoever owns Server obj can use this to shutdown Server
*/
bool Server::check_want_exit()
{
  return this->want_exit;
}

/*
* creates all the related objects and threads
*/
void Server::start()
{
  create_thread_objs();
  create_thread_handles();
}

/*
* ___
*/
void Server::exit()
{
  // send exit signal to all threads
  // join all threads

}

/*
* create all the supporting objects for threads
*/
void create_thread_objs()
{
  // make master thread object
  this->master_thread_object = std::make_unique<Thread_master>(this->num_thread);

  // for every slave thread
  for(int i = 0; i < this->num_thread; i++)
  {
    // make a shared channel
    std::shared_ptr<Channel_master_slave> channel_master_slave_tmp = std::make_shared<Channel_master_slave>();

    // create slave thread object, tell them their respective shared channel and a thread id;
    std::shared_ptr<Thread_slave> slave_tmp = std::make_shared<Thread_slave>(channel_master_slave_tmp, i);

    // make sure to also give the channel to master_thread_obj as well
    this->master_thread_object.add_queue_to_list(channel_master_slave_tmp);

    // save them to server object
    v_slave_thread_object.emplace_back(slave_tmp);
    p_channel_master_slave_list.emplace_back(channel_master_slave_tmp);

  }
}

/*
* launch threads here
*/
void create_thread_handles()
{
  // launch master_thread
  thread_master_handle = std::thread(&Thread_master::thread_function, master_thread_object;

  // launch slave threads
  for(int i = 0; i < this->num_thread; i++)
  {
    std::thread tmp(&Thread_slave::thread_function, v_slave_thread_object[i];
    thread_slave_handle_list.push_back(tmp);
  }
}
