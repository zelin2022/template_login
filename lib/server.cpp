/*
* Filename: server.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Server implementations
* Instruction:
*/

#include "server.hpp"


/*
* @param:hostname the ip address of server
* @param:port The port of the server
* @param:num_thread The number of thread to launch
* @param:socket_per_thread The number of sockets each thread supports
*/
Server::Server(std::string hostname, std::string port, int num_thread, int socket_per_thread)
{
  this->hostname = hostname;
  this->port = port;
  if(num_thread > SERVER_NUM_THREAD_MAX || num_thread < SERVER_NUM_THREAD_MIN){
    throw std::runtime_error("Server created with wrong num_thread value : " + std::to_string(num_thread));
  }
  if(socket_per_thread > SERVER_SOCKET_PER_THREAD_MAX || socket_per_thread < SERVER_SOCKET_PER_THREAD_MIN){
    throw std::runtime_error("Server created with wrong socket_per_thread value : " + std::to_string(socket_per_thread));
  }
  this->num_thread = num_thread;
  this->socket_per_thread = socket_per_thread;

  this->listener_sock = -1;

  v_slave_thread_object.reserve(num_thread);
  p_channel_master_slave_list.reserve(num_thread);
  p_session_count_list.reserve(num_thread); //
  thread_slave_handle_list.reserve(num_thread);
}

/*
*
*/
void Server::give_command(std::string command)
{
  if(command.compare(0,5, "start") == 0)
  {

  }else if(){

  }
}

/*
*
*/
bool Server::check_want_exit()
{
  return this->want_exit;
}

/*
*
*/
void Server::start()
{
  create_thread_objs();
  create_thread_handles();
}

/*
*
*/
void Server::exit()
{
  // send exit signal to all threads
  // join all threads

}

/*
*
*/
void create_thread_objs()
{
  // make master thread object
  if(this->listner_sock < 0){
    throw std::runtime_error("listener socket not initialized");
  }
  this->master_thread_object = std::make_unique<Thread_master>(new Thread_master(this->listner_sock, this->num_thread));

  // for every slave thread
  for(int i = 0; i < this->num_thread; i++)
  {
    // make a shared queue, and a shared session count
    std::shared_ptr<Channel_master_slave> channel_master_slave_tmp = std::make_shared<Channel_master_slave>();

    // create slave thread object, tell them their respective shared queue, shared atomic int, and a thread id;
    std::shared_ptr<Thread_slave> slave_tmp = std::make_shared<Thread_slave>(channel_master_slave_tmp, i);
    this->master_thread_object.add_queue_to_list(channel_master_slave_tmp);

    // save them to server object
    v_slave_thread_object.emplace_back(slave_tmp);
    p_channel_master_slave_list.emplace_back(channel_master_slave_tmp);

  }
}

/*
*
*/
void create_thread_handles()
{
  thread_master_handle = std::thread();
  for(int i = 0; i < this->num_thread; i++)
  {
    std::thread tmp(&Thread_slave::thread_function, &v_slave_thread_object[i]);
    thread_slave_handle_list.push_back(tmp);
  }
}

/*
*
*/
int create_listener_sock(){
  int sockfd;
  struct addrinfo hints, *myinfo, *p;
  memset(&hints, 0, sizeof (hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP

  int rv;
  if ((rv = getaddrinfo(this->hostname.c_str(), this->port.c_str(), &hints, &myinfo)) != 0) {
    throw std::runtime_error("getaddrinfo()");
  }


  for(p = myinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      continue;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      continue;
    }
    break;
  }

  freeaddrinfo(myinfo); // all done with this structure

  if (p == NULL)  {
    throw std::runtime_error("failed to create sock: end of linked list");
  }

  int flags = fcntl(sockfd, F_GETFL, 0);
  fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

  this->mysock = sockfd;
  return sockfd;
}
