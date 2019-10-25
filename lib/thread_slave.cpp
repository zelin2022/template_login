/*
* Filename: thread_slave.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_slave implementations
* Instruction:
*/
#include <poll.h>
#include "thread_slave.hpp"
#include "channel_master_slave.hpp"
#include "session.hpp"
#include "db_con.hpp"
#include "channel_master_slave.hpp"
#include "macro.h"
#include <iostream>

/*
* Constructor
*/
Thread_slave::Thread_slave(
  std::shared_ptr<Channel_master_slave> t_comm,
  int t_id,
  std::atomic<bool> *t_should_i_continue_,
  std::atomic<bool> *t_thread_wants_to_continue_
)
:
m_id(t_id),
m_channel(t_comm),
m_should_i_continue_(t_should_i_continue_),
m_thread_wants_to_continue_(t_thread_wants_to_continue_)
{
  this->m_num_session = 0;
  this->m_pollfd_list = (struct pollfd*)calloc(SLAVE_SOCKET_PER_THREAD_MAX, sizeof(struct pollfd));
}

/*
* Destructor;
*/
Thread_slave::~Thread_slave()
{
  delete this->m_should_i_continue_;
  delete this->m_thread_wants_to_continue_;
  free(this->m_pollfd_list);
}

/*
* everything a slave does
*/
void Thread_slave::thread_function()
{
  #ifdef _DEBUG
  std::cout<<"Thread_slave "<<this->m_id<<", ThreadFunction, start\n";
  #endif

  this->m_db_con = std::make_shared<DB_con>(DATABASE_TARGET_DATABASE, DATABASE_CONNECT_HOSTNAME, DATABASE_CONNECT_USERNAME, DATABASE_CONNECT_PASSWORD);
  while(*this->m_should_i_continue_)
  {
    // vector to receive sockets from channel
    std::vector<int> new_socks;

    // try getting socket from queue until queue is locked or queue is empty
    // current socks and received sockets should not exceed max allowed sockets

    int num_new_socks_received = 0;
    while(this->m_num_session + num_new_socks_received < SLAVE_SOCKET_PER_THREAD_MAX)
    {
      int temp_sock = -1;
      if(this->m_channel->pop(&temp_sock, 0))
      {
        new_socks.push_back(temp_sock);
        num_new_socks_received ++;
      }
      else
      {
        break;
      }
    }


    // for every new socket
    for(int i = 0; i < num_new_socks_received; ++i)
    {
      // make a new session on heap
      std::shared_ptr<Session> session_temp = std::make_shared<Session>(new_socks[i], this->m_db_con);

      // if there is no gaps
      // then append new session and sockfd to the end
      if(this->m_gaps.empty())
      {
        this->m_session_list.push_back(session_temp);
        this->init_pollfd(this->m_pollfd_list[this->m_num_session], new_socks[i]);
      }
      // if there are gaps
      // fill the gaps
      else
      {
          this->m_session_list[this->m_gaps.back()] = session_temp;
          this->init_pollfd(this->m_pollfd_list[this->m_gaps.back()], new_socks[i]);
          this->m_gaps.pop_back();
      }
      this->m_num_session++;
    }

    this->rearrange();

    std::vector<int> polled_sessions = this->mypoll();

    int num_active = polled_sessions.size();

    if(num_active == 0)
    {
      std::this_thread::yield();
    }
    else
    {
      for(int j = 0; j < num_active;  ++j)
      {
        this->m_session_list[j]->do_session();
      }

      // not sure if here
    }

    // or here
    // drop connection
      // close fd
      // decrement num_session
      // add to gaps





  }


  // loop broken, exit phase
  this->safe_exit();





}

/*
* used to swap 2 the position of 2 sessions and their pollfd
*/
void Thread_slave::swap_pollfd_and_session_list(int t_important, int t_throwaway)
{
  this->m_pollfd_list[t_throwaway] = this->m_pollfd_list[t_important];
  this->m_session_list[t_throwaway] = this->m_session_list[t_important];
}

/*
* initiate a pollfd
*/
void Thread_slave::init_pollfd(struct pollfd & t_fd, int t_sock)
{
  t_fd.fd = t_sock;
  t_fd.events = POLLIN;
}

/*
*
*/
void Thread_slave::rearrange()
{
  // if no gaps, then no need to rearrange
  if(this->m_gaps.empty())
  {
    return;
  }

  // first, find out all the gaps between 0<= gaps <num_session, these are gaps that need to be filled
  // then find out all the valids between num_session<= valid < num_gaps + num_sessions which will fill the gap

  std::vector<int> to_be_filled;
  std::vector<int> to_be_swap_in;
  for(unsigned int j = this->m_num_session; j < this->m_gaps.size() + this->m_num_session; ++j)
  {
    to_be_swap_in.push_back(j);
  }

  for(unsigned int i = 0; i < this->m_gaps.size(); ++i)
  {
    if(this->m_gaps[i] < this->m_num_session)
    {
      to_be_filled.push_back(this->m_gaps[i]);
    }
    else
    {
      std::swap(to_be_swap_in[this->m_gaps[i]-this->m_num_session], to_be_swap_in.back());
      to_be_swap_in.pop_back();
    }
  }

  // then we can just swap all of them

  for(unsigned int k = 0; k < to_be_filled.size(); ++k)
  {
    this->swap_pollfd_and_session_list(to_be_swap_in[k], to_be_filled[k]);
  }
  this->m_gaps.clear();
}

/*
* poll(), returns all the session id in a vector
*/
std::vector<int> Thread_slave::mypoll()
{
  std::vector<int> output;
  int num_active = poll(this->m_pollfd_list, this->m_num_session, SLAVE_POLL_TIMEOUT);
  for(int i = 0; i < this->m_num_session; ++i){
    if(this->m_pollfd_list[i].revents && POLLIN)
    {
      output.push_back(i);
    }
  }
  if((int)output.size() != num_active)
  {
    throw std::runtime_error("poll() revents and return miss-match");
  }
  return output;
}

/*
*
*/
void Thread_slave::safe_exit()
{

}
