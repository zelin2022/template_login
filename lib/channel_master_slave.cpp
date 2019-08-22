/*
* Filename: shared_master_slave_channel.cpp
* Author: Zelin Liu
* Date: 2019/08/21
* Description: Shared_queue implementations
* Instruction:
*/

#include "Channel_master_slave.hpp"

/*
*
*/
Channel_master_slave::Channel_master_slave(){}

/*
*
*/
Channel_master_slave::~Channel_master_slave(){}

/*
*
*/
bool Channel_master_slave::push(int &item, bool blocking){
  if(blocking){
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push_back(item);
    mlock.unlock();
    return 1;
  }else{
    std::unique_lock<std::mutex> mlock(mutex_, std::defer_lock);
    if (mlock.try_lock()){
      queue_push_back(item);
      mlock.unlock();
      return 1;
    }
    return 0;
  }
}

/*
*
*/
bool Channel_master_slave::push(int &&item, bool blocking){
  if(blocking)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push_back(std::move(item));
    mlock.unlock();
    return 1;
  }
  else
  {
    std::unique_lock<std::mutex> mlock(mutex_, std::defer_lock);
    if (mlock.try_lock())
    {
      queue_.push_back(std::move(item));
      mlock.unlock();
      return 1;
    }
    return 0;
  }
}

/*
*
*/
int Channel_master_slave::pop(int* output, bool blocking){
  if(blocking)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    if(queue_.empty()){
      mlock.unlock();
      return 0;
    }
    *output = queue_.front();
    queue_.pop_front();
    mlock.unlock();
    return 1;
  }
  else
  {
    std::unique_lock<std::mutex> mlock(mutex_, std::defer_lock);
    if (mlock.try_lock())
    {
      if(queue_.empty()){
        mlock.unlock();
        return 0;
      }
      *output = queue_.front();
      queue_.pop_front();
      mlock.unlock();
      return 1;
    }
    return 0;
  }
}

/*
*
*/
int Channel_master_slave::get_count(int* output, bool blocking);{
  if(blocking)
  {
    std::unique_lock<std::mutex> mlock(mutex_count);
    *output = this->slave_session_count_;
    mlock.unlock();
    return 1;
  }
  else
  {
    std::unique_lock<std::mutex> mlock(mutex_count, std::defer_lock);
    if (mlock.try_lock())
    {
      *output = this->slave_session_count_;
      mlock.unlock();
      return 1;
    }
    return 0;
  }
}

/*
*
*/
void Channel_master_slave::set_count(int count, bool blocking){
  if(blocking)
  {
    std::unique_lock<std::mutex> mlock(mutex_count);
    this->slave_session_count_ = count;
    mlock.unlock();
    return 1;
  }
  else
  {
    std::unique_lock<std::mutex> mlock(mutex_count, std::defer_lock);
    if (mlock.try_lock())
    {
      this->slave_session_count_ = count;
      mlock.unlock();
      return 1;
    }
    return 0;
  }
}

/*
*
*/
void Channel_master_slave::add_count(int to_add, bool blocking){
  if(blocking)
  {
    std::unique_lock<std::mutex> mlock(mutex_count);
    this->slave_session_count_ += to_add;
    mlock.unlock();
    return 1;
  }
  else
  {
    std::unique_lock<std::mutex> mlock(mutex_count, std::defer_lock);
    if (mlock.try_lock())
    {
      this->slave_session_count_ += to_add;
      mlock.unlock();
      return 1;
    }
    return 0;
  }
}
