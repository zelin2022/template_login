/*
* Filename: thread_slave.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_slave implementations
* Instruction:
*/
#ifndef _THREAD_SLAVE_HPP_
#define _THREAD_SLAVE_HPP_

#include <poll.h>

#include "channel_master_slave.hpp"
class Thread_slave{
public:
  Thread_slave(std::shared_ptr<Channel_master_slave> comm, int id);
  ~Thread_slave();

  void thread_function();

private:

  int id;
  std::shared_ptr<Channel_master_slave> channel;

  std::vector<std::shared_ptr<Session>> session_list;
  struct pollfd* pollfd_list;

  int num_session;
  std::vector<int> gaps;


  void swap_pollfd_and_session_list(struct pollfd &important, struct pollfd &throwaway);
  static void init_pollfd(struct pollfd &fd, int sock);
  void rearrange();
  std::vector<int> mypoll();

};
#endif
