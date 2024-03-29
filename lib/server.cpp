/*
* Filename: server.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Server implementations
* Instruction:
*/

#include "server.hpp"

#include "channel_master_slave.hpp"
#include "thread_master.hpp"
#include "thread_slave.hpp"
#include <string>
#include "macro.h"
#include "iostream"



/*
* Constructor for SERVER
*/
Server::Server(std::string t_hostname, std::string t_port, int t_num_thread, int t_socket_per_thread)
: m_hostname(t_hostname), m_port(t_port), m_num_thread(t_num_thread), m_socket_per_thread(t_socket_per_thread)
{

  // boundary check given values with macros defined in macro.h
  if(t_num_thread > SERVER_NUM_THREAD_MAX || t_num_thread < SERVER_NUM_THREAD_MIN){
    throw std::runtime_error("Server created with wrong num_thread value : " + std::to_string(t_num_thread));
  }
  if(t_socket_per_thread > SLAVE_SOCKET_PER_THREAD_MAX || t_socket_per_thread < SLAVE_SOCKET_PER_THREAD_MIN){
    throw std::runtime_error("Server created with wrong socket_per_thread value : " + std::to_string(t_socket_per_thread));
  }



  m_v_slave_thread_object.reserve(t_num_thread);
  m_v_channel_master_slave_list.reserve(t_num_thread);
  m_thread_slave_handle_list.reserve(t_num_thread);

  this->m_want_exit = false;
}


/*
* Destructor for SERVER
*/
Server::~Server()
{

}

// /*
// * do something for cetain commands:
// * ____
// */
// void Server::give_command(std::string t_cmd)
// {
//   #ifdef _DEBUG
//   std::cout<<"Command : "+t_cmd<<std::endl;;
//   #endif
//   if(t_cmd.compare(0,5, "start") == 0)
//   {
//     #ifdef _DEBUG
//     std::cout<<"start"<<std::endl;
//     #endif
//     this->start();
//   }
//   else
//   {
//     std::cout<<"-Invalid Command-\n";
//   }
//   // else if()
//   // {
//
//   // }
// }

/*
* returns the bool value of a flag
* whoever owns Server obj can use this to shutdown Server
*/
bool Server::check_want_exit()
{
  return this->m_want_exit;
}

/*
* creates all the related objects and threads
*/
void Server::start()
{
  this->create_thread_objs();
  #ifdef _DEBUG
  std::cout<< "create_thread_objs() done\n";
  #endif
  this->create_thread_handles();
  #ifdef _DEBUG
  std::cout<< "create_thread_handles() done\n";
  #endif
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
void Server::create_thread_objs()
{

  #ifdef _DEBUG
  std::cout<<"create_thread start"<<std::endl;
  #endif

  // this->m_flag_master_should_i_continue_=std::make_shared<std::atomic<bool>>();
  // this->m_flag_master_should_i_continue_->store(true);
  this->m_flag_master_should_i_continue_= new std::atomic<bool>(true);
  this->m_flag_master_thread_wants_to_continue_ = new std::atomic<bool>(true);
  // test.store(false);
  // this->m_flag_master_thread_wants_to_continue_=std::make_shared<std::atomic<bool>>(true);

  // make master thread object
  this->m_master_thread_object = std::make_shared<Thread_master>(
    this->m_num_thread,
    this->m_hostname,
    this->m_port,
    this->m_flag_master_should_i_continue_,
    this->m_flag_master_thread_wants_to_continue_
  );

  // for every slave thread
  for(int i = 0; i < this->m_num_thread; i++)
  {
    // make a shared channel
    std::shared_ptr<Channel_master_slave> channel_master_slave_tmp = std::make_shared<Channel_master_slave>();

    std::atomic<bool> *tmp_flag_slave_should_i_continue_=new std::atomic<bool>(true);
    std::atomic<bool> *tmp_flag_slave_thread_wants_to_continue_=new std::atomic<bool>(true);
    // create slave thread object, tell them their respective shared channel and a thread id;
    std::shared_ptr<Thread_slave> slave_tmp = std::make_shared<Thread_slave>(
      channel_master_slave_tmp,
      i,
      tmp_flag_slave_should_i_continue_,
      tmp_flag_slave_thread_wants_to_continue_
    );
    this->m_v_flag_slave_should_i_continue_.emplace_back(tmp_flag_slave_should_i_continue_);
    this->m_v_flag_slave_thread_wants_to_continue_.emplace_back(tmp_flag_slave_thread_wants_to_continue_);


    // make sure to also give the channel to master_thread_obj as well
    this->m_master_thread_object->AddQueueToList(channel_master_slave_tmp);

    // save them to server object
    this->m_v_slave_thread_object.emplace_back(slave_tmp);
    this->m_v_channel_master_slave_list.emplace_back(channel_master_slave_tmp);

  }
}

/*
* launch threads here
*/
void Server::create_thread_handles()
{
  // launch master_thread
  this->m_thread_master_handle = std::thread(&Thread_master::ThreadFunction, m_master_thread_object);

  // launch slave threads
  for(int i = 0; i < this->m_num_thread; i++)
  {
    std::thread tmp(&Thread_slave::thread_function, m_v_slave_thread_object[i]);
    this->m_thread_slave_handle_list.push_back(std::move(tmp));
  }
}
