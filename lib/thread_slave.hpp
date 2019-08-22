/*
* Filename: thread_slave.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_slave implementations
* Instruction:
*/
#ifndef _THREAD_SLAVE_HPP_
#define _THREAD_SLAVE_HPP_

#include "channel_master_slave.hpp"
class Thread_slave{
public:
  Thread_slave(std::shared_ptr<Channel_master_slave> comm, int id);

  void thread_function();

private:
  std::shared_ptr<Channel_master_slave> channel;
  std::vector<std::shared_ptr<Session>> session_list;
  int id;

};
#endif
