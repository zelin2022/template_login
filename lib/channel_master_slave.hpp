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
private:
  std::deque<int> queue_;
  std::mutex mutex_;
  std::mutex mutex_count;
  // std::condition_variable cond_;
  int slave_session_count_;
public:
  Channel_master_slave();
  ~Channel_master_slave();
  bool push(int& item, bool blocking);
  bool push(int&& item, bool blocking);
  bool pop(int* output, bool blocking);
  bool get_count(int* output, bool blocking);
  void set_count(int count, bool blocking);

};
#endif
