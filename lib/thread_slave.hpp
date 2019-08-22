/*
* Filename: thread_slave.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_slave implementations
* Instruction:
*/
#ifndef _THREAD_SLAVE_HPP_
#define _THREAD_SLAVE_HPP_

#include "shared_queue.hpp"
class Thread_slave{
public:
  Thread_slave(std::shared_ptr<Shared_queue_mod0<int>> sock_queue);

  void thread_function();

private:
  std::shared_ptr<Shared_queue_mod0<int>> sock_queue;
  std::vector<std::shared_ptr<Session>> session_list;

};
#endif
