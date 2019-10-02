/*
* Filename: thread_slave.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_slave implementations
* Instruction:
*/
#ifndef _THREAD_SLAVE_HPP_
#define _THREAD_SLAVE_HPP_


// #include "session.hpp"
// #include "db_con.hpp"
#include <thread>
#include <atomic>
#include <vector>
#include <memory>

class Session;
class DB_con;
class Channel_master_slave;
// #include "channel_master_slave.hpp"
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

  int m_id;
  std::shared_ptr<Channel_master_slave> m_channel;
  std::vector<std::shared_ptr<Session>> m_session_list;
  struct pollfd* m_pollfd_list;

  int m_num_session;
  std::vector<int> m_gaps;
  std::shared_ptr<DB_con> m_db_con;
  std::shared_ptr<std::atomic<bool>> m_should_i_continue_;
  std::shared_ptr<std::atomic<bool>> m_thread_wants_to_continue_;

  std::vector<int> mypoll();
  void swap_pollfd_and_session_list(int t_important, int t_throwaway);
  static void init_pollfd(struct pollfd &t_fd, int t_sock);
  void rearrange();
  void safe_exit();


};
#endif
