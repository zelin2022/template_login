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
#include "session.hpp"
#include "db_con.hpp"
#include <thread>
#include <atomic>
#include "channel_master_slave.hpp"
class Thread_slave{
public:

  /*
  * @param comm shared_ptr of communication channel between master and slave
  * @para id slave therad id
  */
  Thread_slave(
    std::shared_ptr<Channel_master_slave> comm,
    int id,
    std::atomic_flag should_i_continue_,
    std::atomic_flag thread_wants_to_continue_
  );

  ~Thread_slave();

  void thread_function();

private:

  int id;
  std::shared_ptr<Channel_master_slave> channel;

  std::vector<std::shared_ptr<Session>> session_list;
  struct pollfd* pollfd_list;

  int num_session;
  std::vector<int> gaps;

  std::shared_ptr<DB_con> db_con;
  std::atomic_flag should_i_continue;

  void swap_pollfd_and_session_list(int important, int throwaway);
  static void init_pollfd(struct pollfd &fd, int sock);
  void rearrange();
  std::vector<int> mypoll();

};
#endif
