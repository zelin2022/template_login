/*
* Filename: thread_master.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_master implementations
* Instruction:
*/
#ifndef _THREAD_MASTER_HPP_
#define _THREAD_MASTER_HPP_

class Listener;
class Channel_master_slave;

#include <memory>
#include <atomic>
#include <vector>
#include <deque>


class Thread_master{
public:
  /*
  * @param num_slaves the total number of slave threads
  */
  Thread_master(
    int t_num_slaves,
    std::string t_hostname,
    std::string t_port,
    std::atomic<bool> *t_should_i_continue_,
    std::atomic<bool> *t_thread_wants_to_continue_
  );

  ~Thread_master();

  /*
  * @param to_add the shared_ptr of a communication channel to add to list
  */
  void AddQueueToList(std::shared_ptr<Channel_master_slave> t_to_add);

  /*
  * thread function to be run
  */
  void ThreadFunction();


private:

  void GetSock();
  void Distribute();
  void UpdateCount();
  void SortSessionCount();
  void exit();

  std::atomic<bool> *m_should_i_continue;
  std::atomic<bool> *m_thread_wants_to_continue;

  std::shared_ptr<Listener> m_listener;
  std::vector<std::shared_ptr<Channel_master_slave>> m_channel_list;
  std::vector<std::pair<int,int>> m_vector_slave_session_count;

  std::shared_ptr<std::deque<int>> m_new_socks;
};

#endif
