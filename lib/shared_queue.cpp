/*
* Filename: server.cpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread implementations
* Instruction:
*/

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
