/*
* Filename: thread_master.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_master implementations
* Instruction:
*/
#ifndef _THREAD_MASTER_HPP_
#define _THREAD_MASTER_HPP_

#include "channel_master_slave.hpp"

class Thread_master{
public:
  Thread_master(int sock);
  void thread_function();
  void add_queue_to_list(std::shared_ptr<Channel_master_slave>);
private:
  void get_their_sock_then_distribute();
  void equal_distribute(std::queue to_be_distributed);
  int listener_sock;
  std::vector<std::shared_ptr<Channel_master_slave>> channel_list;
  std::map<int,int> slave_session_count;
};

#endif
