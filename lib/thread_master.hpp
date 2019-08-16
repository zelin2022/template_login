/*
* Filename: thread_master.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_master implementations
* Instruction:
*/
#ifndef _THREAD_MASTER_HPP_
#define _THREAD_MASTER_HPP_
class Thread_master{
public:
  Thread_master();
  virtual void thread_function();
  int add_queue_to_list(std::shared_ptr<Shared_queue<int>>);
private:
  std::vector<Shared_queue<int>*> sock_queue_list;
  std::vector<int> slave_sock_count;
};

#endif
