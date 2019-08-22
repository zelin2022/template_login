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
Thread_master::Thread_master(int sock){
  this->lisnter_sock = sock;
}

/*
*
*/
void Thread_master::thread_function(){
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
void Thread_master::add_queue_to_list(std::shared_ptr<Channel_master_slave> que){
  this->queue_list.push_back(que);
}

/*
*
*/
void Thread_master::get_their_sock_then_distribute(){

  // storage for their addr, can be used later;
  struct sockaddr_storage target_addr;
  memset(&target_addr, 0, sizeof(sockaddr_storage));
  socklen_t target_addr_len = sizeof(target_addr);

  while(true){
    int their_sock = accept(this->mysock, their_addr, sin_size);
    if(their_sock < 0){
      perror("accept()");
      throw std::ruentime_error("accept()");
    }
    // check all
    for(int i = 0; i < this->slave_sock_count.size(); i ++){

    }
  }
}
