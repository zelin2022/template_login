/*
* Filename: thread_master.cpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_master implementations
* Instruction:
*/

#include "thread_master.hpp"
/*
* constructor for Thread_master class
* uses get addrinfo() to get a valid addr
* then creates socket
* set it to O_NONBLOCK
* set it to SO_REUSEADDR
* bind it to addr
*/
Thread_master::Thread_master(int num_slaves,
  std::string hostname,
  std::string port,
  std::bool_flag should_i_continue_,
  std::atmoic_flag thread_wants_to_continue_
)
{

  this->should_i_continue = should_i_continue_;
  this->thread_wants_to_continue = thread_wants_to_continue_;
  // create a map for slave_id and their current session count
  for(int i = 0; i <num_thread; i ++){
    this->slave_session_count.insert(std::map<int,int>::value_type(i, 0));
  }

  this->total_slave_sessions = 0;
  this->listener = std::make_shared<Listener>(hostname, port);
}

/*
* starts listening for connection
* then distribute sessions
*/
void Thread_master::thread_function()
{
  // try catch block for thread?

  while(this->should_i_continue.test_and_set()){
    // do whatever
  }


  // exit()

  this->get_their_sock_then_distribute();
}

/*
* add a channel to list
*/
void Thread_master::add_queue_to_list(std::shared_ptr<Channel_master_slave> to_add)
{
  this->queue_list.push_back(to_add);
}

/*
*
*/
void Thread_master::get_their_sock_then_distribute()
{

  // storage for their addr, can be used later;
  struct sockaddr_storage target_addr;
  memset(&target_addr, 0, sizeof(sockaddr_storage));
  socklen_t target_addr_len = sizeof(target_addr);
  std::queue<int> to_be_distributed;

  while(true)
  {

    // accept as many sessions as possible
    // since socket is non_blocking
    // if accept returns -1 then it means no more connections to accept
    while(true)
    {
      int their_sock = accept(this->mysock, their_addr, sin_size);
      if (their_sock < 0)
      {
        break;
      }
      to_be_distributed.push_back(their_sock);
    }

    // check all channels in an attempt to update sock count
    for(int i = 0; i < this->channel_list.size(); i ++)
    {
      int temp = -1;
      if(this->channel_list[i]->get_count(&temp, 0)) // non_blocking, means if mutex is locked then returns false and temp is not updated
      {
        this->total_slave_sessions += temp - this->slave_session_count.at(i);
        this->slave_session_count[i] = temp;
      }
    }

    /*
    some problem here
    i have to distribute the accepted sockets as evenlly as i can to slaves
    all i have are a list of slave sessions, and they are estimates not exact, their exact <= estimate
    best way to distribute:
    */
    this->distribute_mk0(to_be_distributed); // current implementation ^
  }
}

/*
* @param the queue of sockets to be distributed
* iteration 0 of distribution algorithm
*/
void distribute_mk0(std::queue<int>& to_be_distributed)
{

  // create a vector of pairs (slave id, slave session count)
  std::vector<std::pair<int,int>> count_map;
  // fill them
  for(int i = 0; i<slave_session_count.size(); i++)
  {
    count_map.push_back(std::pair<int, int>(i, slave_session_count[i]));
  }
  // then sort it by count
  sort(count_map.begin(), count_map.end(), [=](std::pair<int, int>& a, std::pair<int, int>& b)
    {
      if(a.second == b.second){
        return a.first < b.first;
      }
      return a.second < b.second;
    }
  );

  // start distributing, while the to_be_distributed queue is not empty
  // go through all the sorted(by session count) list and attempt to distribute session
  while(!to_be_distributed.empty()){
    for(int i = 0; i<slave_session_count.size(); i++)
    {
      if(channel_list[count_map[i].first]->push(to_be_distributed.front(), 0) == 1)
      {
        to_be_distributed.pop_front();
        slave_session_count[cout_map[i].first]++;
        if(to_be_distributed.empty())
        {
          break;
        }
      }
    }
  }
}
