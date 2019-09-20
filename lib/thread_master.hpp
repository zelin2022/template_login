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
#include <map>
#include <memory>
#include <atomic>


class Thread_master{
public:
  /*
  * @param num_slaves the total number of slave threads
  */
  Thread_master(
    int num_slaves,
    std::string hostname,
    std::string port, 
    std::atomic_fag should_i_continue_,
    std::atmoic_flag thread_wants_to_continue_
  );

  /*
  * thread function to be run
  */
  void thread_function();

  /*
  * @param to_add the shared_ptr of a communication channel to add to list
  */
  void add_queue_to_list(std::shared_ptr<Channel_master_slave> to_add);
private:
  std::atomic_flag should_i_continue;
  std::atomic_flag thread_wants_to_continue;
  void get_their_sock_then_distribute();
  void distribute_mk0(std::queue<int>& to_be_distributed);
  std::shared_ptr<Listener> listener;
  std::vector<std::shared_ptr<Channel_master_slave>> channel_list;
  std::map<int,int> slave_session_count;
};

#endif
