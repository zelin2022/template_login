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
  Thread_slave(Shared_queue<int>* sock_queue, int* session_count, int thread_id);

  virtual void thread_function();

private:
  int fetch_from_queue();
  std::shared_ptr<Shared_queue<int>> sock_queue;
  std::vector<int> my_socks;
};
#endif
