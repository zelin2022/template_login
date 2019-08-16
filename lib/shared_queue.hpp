/*
* Filename: shared_queue.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Shared_queue implementations
* Instruction:
*/

#ifndef _SHARED_QUEUE_HPP_
#define _SHARED_QUEUE_HPP_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Shared_queue
{
public:
  Shared_queue();
  ~Shared_queue();

  T& front();
  void pop_front();

  void push_back(const T& item);
  void push_back(T&& item);

  int size();
  bool empty();

private:
  std::deque<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};
