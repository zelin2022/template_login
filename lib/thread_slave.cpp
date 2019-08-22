/*
* Filename: thread_slave.hpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_slave implementations
* Instruction:
*/

#include "thread_slave.hpp"
#include "channel_master_slave.hpp"

/*
*
*/
Thread_slave::Thread_slave(std::shared_ptr<Channel_master_slave> comm, int id)
{
  this->channel = comm;
  this->id = id;
}

/*
*
*/
void Thread_slave::thread_function()
{
  while(true)
  {
    std::vector<int> new_socks;

    // try getting socket from queue until queue is locked or queue is empty
    while(true)
    {
      int temp_sock = -1;
      if(this->channel.pop(&temp_sock, 0))
      {
        new_socks.push_back(temp_sock);
      }
      else
      {
        break;
      }
    }

    for(int i = 0; i < new_socks.size(); i++)
    {
      std::shared_ptr<Session> session_temp = std::make_shared(Session(new_socks[i]));
      this->session_list.push_back(session_temp);
    }


  }
}
