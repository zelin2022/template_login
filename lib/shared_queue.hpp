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

template <typename T>
Shared_queue<T>::Shared_queue(){}

template <typename T>
Shared_queue<T>::~Shared_queue(){}

template <typename T>
T& Shared_queue<T>::front()
{
  std::unique_lock<std::mutex> mlock(mutex_);
  while (queue_.empty())
  {
    cond_.wait(mlock);
  }
  return queue_.front();
}

template <typename T>
void Shared_queue<T>::pop_front()
{
  std::unique_lock<std::mutex> mlock(mutex_);
  while (queue_.empty())
  {
    cond_.wait(mlock);
  }
  queue_.pop_front();
}

template <typename T>
void Shared_queue<T>::push_back(const T& item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  queue_.push_back(item);
  mlock.unlock();     // unlock before notificiation to minimize mutex con
  cond_.notify_one(); // notify one waiting thread

}

template <typename T>
void Shared_queue<T>::push_back(T&& item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  queue_.push_back(std::move(item));
  mlock.unlock();     // unlock before notificiation to minimize mutex con
  cond_.notify_one(); // notify one waiting thread

}

template <typename T>
int Shared_queue<T>::size()
{
  std::unique_lock<std::mutex> mlock(mutex_);
  int size = queue_.size();
  mlock.unlock();
  return size;
}
#endif
