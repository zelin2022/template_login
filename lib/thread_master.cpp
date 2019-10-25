/*
* Filename: thread_master.cpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_master implementations
* Instruction:
*/

#include "thread_master.hpp"

#include "channel_master_slave.hpp"
#include "listener.hpp"
#include <algorithm>
#include <iostream>
/*
* constructor for Thread_master class
* uses get addrinfo() to get a valid addr
* then creates socket
* set it to O_NONBLOCK
* set it to SO_REUSEADDR
* bind it to addr
*/
Thread_master::Thread_master(int t_num_slaves,
  std::string t_hostname,
  std::string t_port,
  std::atomic<bool> *t_should_i_continue_,
  std::atomic<bool> *t_thread_wants_to_continue_

):m_should_i_continue(std::move(t_should_i_continue_)),
m_thread_wants_to_continue(std::move(t_thread_wants_to_continue_))
{


  // create a map for slave_id and their current session count
  for(int i = 0; i < t_num_slaves; ++i){
    this->m_vector_slave_session_count.push_back(std::pair<int,int>(i, 0));
  }

  this->m_listener = std::make_shared<Listener>(t_hostname, t_port);
  this->m_new_socks = std::make_shared<std::deque<int>>();


}

Thread_master::~Thread_master()
{
  delete m_thread_wants_to_continue;
  delete m_should_i_continue;
}

/*
* add a channel to list
*/
void Thread_master::AddQueueToList(std::shared_ptr<Channel_master_slave> to_add)
{
  this->m_channel_list.push_back(to_add);
}

/*
* 4 things this thread doesslave_session_count


* checks for incoming sockets
* distribute incoming sockets
* updates socket count
* re-sort

void GetSock();
void Distribute();
void UpdateCount();
void Sort();

*/
void Thread_master::ThreadFunction()
{
  // try catch block for thread?
  // #ifdef _DEBUG
  // std::cout<< this->m_thread_wants_to_continue<<std::endl;
  // std::cout<<"Thread_master, ThreadFunction, start\n" ;
  // #endif

  while(this->m_thread_wants_to_continue)
  {
    // #ifdef _DEBUG
    // std::cout<<"Thread_master, ThreadFunction, whileloop, start\n";
    // #endif
    this->GetSock();
    // #ifdef _DEBUG
    // std::cout<<"Thread_master, ThreadFunction, whileloop, GetSock() complete\n";
    // #endif
    this->Distribute();
    // #ifdef _DEBUG
    // std::cout<<"Thread_master, ThreadFunction, whileloop, Distribute() complete\n";
    // #endif
    this->UpdateCount();
    // #ifdef _DEBUG
    // std::cout<<"Thread_master, ThreadFunction, whileloop, UpdateCount() complete\n";
    // #endif
    this->SortSessionCount();

  }


  this->exit();

}

/*
*
*/
void Thread_master::GetSock()
{
  this->m_listener->AcceptNewSocks(this->m_new_socks);
}

/*
*
*/
void Thread_master::Distribute()
{
  // #ifdef _DEBUG
  // std::cout<<"Thread_master, Distribute(), before loop\n";
  // #endif
  while(!this->m_new_socks->empty())
  {
    // #ifdef _DEBUG
    // std::cout<<"Thread_master, Distribute(), loop start\n";
    // #endif
    for(unsigned int i = 0; i<this->m_vector_slave_session_count.size(); ++i)
    {
      // try pushing, if push failed then move on to the next one.

      //m_vector_slave_session_count is sorted list of slave_id by their session count
      if(this->m_channel_list[this->m_vector_slave_session_count[i].first]->push(this->m_new_socks->front(), 0) == 1)
      {
        this->m_new_socks->pop_front();
        ++this->m_vector_slave_session_count[i].second; // not sure if needed
        if(this->m_new_socks->empty())
        {
          break;
        }
      }
    }
  }
  // #ifdef _DEBUG
  // std::cout<<"Thread_master, Distribute(), loop end\n";
  // #endif
}

/*
*
*/
void Thread_master::UpdateCount()
{
  // check all channels in an attempt to update sock count
  for(unsigned int i = 0; i < this->m_vector_slave_session_count.size(); ++i)
  {
    int temp = -1;
    if(this->m_channel_list[this->m_vector_slave_session_count[i].first]->get_count(&temp, 0)) // non_blocking, means if mutex is locked then returns false and temp is not updated
    {
      this->m_vector_slave_session_count[i].second = temp;
    }
  }

}

/*
*
*/
void Thread_master::SortSessionCount()
{
  std::sort(this->m_vector_slave_session_count.begin(), this->m_vector_slave_session_count.end(), [=](std::pair<int, int>& a, std::pair<int, int>& b)
    {
      if(a.second == b.second){
        return a.first < b.first;
      }
      return a.second < b.second;
    }
  );
}

/*
*
*/
void Thread_master::exit()
{
  this->m_thread_wants_to_continue->store(true); // signal back to main thread that I am ready to be killed
  // really don't have much else.
}
