/*
* Filename: shared_master_slave_channel.hpp
* Author: Zelin Liu
* Date: 2019/08/21
* Description: Shared_queue implementations
* Instruction:
*/

#ifndef _CHANNEL_MASTER_SLAVE_HPP_
#define _CHANNEL_MASTER_SLAVE_HPP_

#include <queue>
#include <mutex>
// #include <condition_variable>

class Channel_master_slave{

public:
  Channel_master_slave();
  ~Channel_master_slave();

  /*
  * @param item the item to be pushed
  * @param blocking, true for blocking, false for non_blocking
  */
  bool push(int& item, bool blocking);
  bool push(int&& item, bool blocking);

  /*
  * @param output item to be poped from queue
  * @param blocking, true for blocking, false for non_blocking
  */
  bool pop(int* output, bool blocking);

  /*
  * @param output returns slave_session_count_
  * @param blocking, true for blocking, false for non_blocking
  */
  bool get_count(int* output, bool blocking);

  /*
  * @param count slave_session_count_ to be set
  * @param blocking, true for blocking, false for non_blocking
  */
  bool set_count(int count, bool blocking);

  /*
  * @param to_add a value to be add to slave_session_count_
  * @param blocking, true for blocking, false for non_blocking
  */
  bool add_count(int to_add, bool blocking);
private:
  std::deque<int> queue_;
  std::mutex mutex_;
  std::mutex mutex_count;
  // std::condition_variable cond_;
  int slave_session_count_;

};
#endif
