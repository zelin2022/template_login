/*
* Filename: thread_master.cpp
* Author: Zelin Liu
* Date: 2019/08/14
* Description: Thread_master implementations
* Instruction:
*/

/*
*
*/
Thread_master::Thread_master(int sock, int num_slaves)
{
  this->listener_sock = sock;
  for(int i = 0; i <num_thread; i ++){
    this->slave_session_count.insert(std::map<int,int>::value_type(i, 0));
  }

  this->total_slave_sessions = 0;
}

/*
*
*/
void Thread_master::thread_function()
{
  // try catch block
  if (listen(this->mysock, LISTENER_MAX_LISTEN_BACKLOG) == -1) {
    perror("listen()");
    throw std::runtime_error("listen()");
  }

  this->get_their_sock_then_distribute();


}

/*
*
*/
void Thread_master::add_queue_to_list(std::shared_ptr<Channel_master_slave> que)
{
  this->queue_list.push_back(que);
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
    while(true)
    {
      int their_sock = accept(this->mysock, their_addr, sin_size);
      if (their_sock < 0)
      {
        break;
      }
      to_be_distributed.push_back(their_sock);
    }

    // check all in an attempt to update sock count
    for(int i = 0; i < this->channel_list.size(); i ++)
    {
      int temp = -1;
      if(this->channel_list[i].get()->get_count(&temp, 0))
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
    this->distribute(to_be_distributed);
  }
}

/*
*
*/
void equal_distribute(std::queue& to_be_distributed)
{
  std::vector<std::pair<int,int>> count_map;
  for(int i = 0; i<slave_session_count.size(); i++)
  {
    count_map.push_back(std::pair<int, int>(i, slave_session_count[i]));
  }
  sort(count_map.begin(), count_map.end(), [=](std::pair<int, int>& a, std::pair<int, int>& b)
    {
      if(a.second == b.second){
        return a.first < b.first;
      }
      return a.second < b.second;
    }
  );
  while(!to_be_distributed.empty()){
    for(int i = 0; i<slave_session_count.size(); i++)
    {
      if(channel_list[count_map[i].first].get()->push(to_be_distributed.front(), 0) == 1)
      {
        to_be_distributed.pop_front();
        if(to_be_distributed.empty())
        {
          break;
        }
      }
    }
  }
}
