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
    std::shared_ptr<Channel_master_slave> t_comm,
    int t_id,
    std::shared_ptr<std::atomic<bool>> t_should_i_continue_,
    std::shared_ptr<std::atomic<bool>> t_thread_wants_to_continue_
  );

  ~Thread_slave();

  void thread_function();

private:

  int id;
  std::shared_ptr<Channel_master_slave> channel;
  std::vector<std::shared_ptr<Session>> session_list;
  struct pollfd* pollfd_list;
  std::vector<int> mypoll();
  int num_session;
  std::vector<int> gaps;
  std::shared_ptr<DB_con> db_con;
  std::shared_ptr<std::atomic<bool>> should_i_continue_;
  std::shared_ptr<std::atomic<bool>> thread_wants_to_continue_;

  void swap_pollfd_and_session_list(int important, int throwaway);
  static void init_pollfd(struct pollfd &fd, int sock);
  void rearrange();
  void safe_exit();


};
#endif
