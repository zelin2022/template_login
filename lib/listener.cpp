// not used
/*
* Filename: listener.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Listener implementation
* Instruction:
*/

#include "macro.h"
#include "listener.hpp"

/*
*
*/
Listener::Listener(std::string hostname, std::string port)
{
  this->hostname = hostname;
  this->port = port;
}

/*
*
*/
int Listener::init()
{
  int sockfd;
  struct addrinfo hints, *myinfo, *p;
  memset(&hints, 0, sizeof (hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int rv;
  if ((rv = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &myinfo)) != 0)
  {
    fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(rv));
    return -1;
  }

  for(p = myinfo; p != NULL; p = p->ai_next)
  {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
    {
      perror("server: socket");
      continue;
    }

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      perror("setsockopt");
      continue;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
    {
      close(sockfd);
      perror("server: bind");
      continue;
    }

    break;
  }

  freeaddrinfo(myinfo); // all done with this structure

  if (p == NULL)
  {
    fprintf(stderr, "my addr: failed\n");
    return(-1);
  }

  this->mysock = sockfd;
  return 0;
}

/*
*
*/
bool Listener::set_sock_nonblocking(int sock, bool non_blocking)
{
  if (sock < 0){return false;}
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {return false;}
  flags = non_blocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
  return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
}

/*
*
*/
int start_listen()
{
  if(this->is_listening)
  { //already listen() ????
    return 1;
  }
  if (listen(this->mysock, LISTENER_MAX_LISTEN_BACKLOG) == -1)
  {
    perror("listen");
    return -1;
  }
  this->is_listening = true;
  return 0;
}

/*
*
*/
int get_connection(struct sockaddr& their_addr, socklen_t& sin_size)
{
  if(!this->is_listening)
  {
    printf("accept() failed because is_listening is false\n");
    return -1;
  }
  int ret = accept(this->mysock, &their_addr, &sin_size);
  // if(ret == -1){
  //   perror("accept");
  // }
  return ret;
}
