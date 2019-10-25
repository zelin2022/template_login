// not used
/*
* Filename: listener.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Listener implementation
* Instruction:
*/

#include "listener.hpp"

// #include <string>
// #include <vector>
// #include <memory>
#include <deque>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include "macro.h"
#include <netdb.h>
#include <arpa/inet.h>
#ifdef _DEBUG
#include <iostream>
#endif
/*
*
*/
Listener::Listener(std::string t_hostname, std::string t_port)
:m_hostname(t_hostname), m_port(t_port)
{
  this->connect();
}

/*
*
*/
Listener::~Listener()
{
  close(this->m_listener_sock);
}


/*
*
*/
void Listener::connect()
{
  // socket
  int sockfd;
  struct addrinfo hints, *myinfo, *p;
  memset(&hints, 0, sizeof (hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int rv;
  if ((rv = getaddrinfo(this->m_hostname.c_str(), this->m_port.c_str(), &hints, &myinfo)) != 0) {
    throw std::runtime_error("getaddrinfo()");
  }


  for(p = myinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      close(sockfd);
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

  if(!this->set_sock_nonblocking(this->m_listener_sock, true))
  {
      perror("set_sock_nonblocking()");
      throw std::runtime_error("set_sock_nonblocking()");
  }

  if (listen(sockfd, LISTENER_MAX_LISTEN_BACKLOG) == -1) {
    perror("listen()");
    throw std::runtime_error("listen()");
  }

  #ifdef _DEBUG
  std::cout<<"listening\n";
  #endif

  this->m_listener_sock = sockfd;
}

/*
*
*/
int Listener::get_listener_sock()
{
  return this->m_listener_sock;
}



/*
*
*/
void Listener::AcceptNewSocks(std::shared_ptr<std::deque<int>> t_queue)
{
  while(true)
  {
    struct sockaddr_storage their_addr;
    memset(&their_addr, 0, sizeof(sockaddr_storage));
    socklen_t sin_size = sizeof(their_addr);

    int their_sock = accept(this->m_listener_sock, (struct sockaddr *)&their_addr, &sin_size);

    if (their_sock < 0)
    {
      break;
    }

    #ifdef _DEBUG
    std::cout<<"received a conncetion\n";
    this->print_addr(their_addr);
    #endif
    t_queue->push_back(their_sock);
  }
}


/*
*
*/
bool Listener::set_sock_nonblocking(int t_sock, bool non_blocking)
{
  if (t_sock < 0){return false;}
  int flags = fcntl(t_sock, F_GETFL, 0);
  if (flags == -1) {return false;}
  flags = non_blocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
  return (fcntl(t_sock, F_SETFL, flags) == 0) ? true : false;
}

/*
* Function: print_addr
* Input: sockaddr struct contains peer's ip and port
* Output: none
* Description: checks if IPV4 or IPV6 then prints the details
*/
void Listener::print_addr(struct sockaddr_storage addr)
{

  printf("Connection received:\n");

  // checks ipv4 or ipv6, then print them accordingly
  if(addr.ss_family == AF_INET){
    char p_ip[INET_ADDRSTRLEN];
    struct sockaddr_in *p = (sockaddr_in*)&addr;
    if(NULL==inet_ntop(addr.ss_family, &(p->sin_addr), p_ip, INET_ADDRSTRLEN)){
      perror("inet_ntop, v4");
    }
    printf("IPv4\n IP:%s\n Port:%d \n", p_ip, ntohs(p->sin_port));
  }else if(addr.ss_family == AF_INET6){
    char p_ip[INET6_ADDRSTRLEN];
    struct sockaddr_in6 *p = (sockaddr_in6*)&addr;
    if(NULL==inet_ntop(addr.ss_family, &(p->sin6_addr), p_ip, INET6_ADDRSTRLEN)){
      perror("inet_ntop, v6");
    }
    printf("IPv6\n IP:%s\n Port:%d \n", p_ip, ntohs(p->sin6_port));
  }else{
    printf("neither ipv4 or ipv6\n");
  }
}
