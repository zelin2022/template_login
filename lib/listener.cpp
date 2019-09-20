// not used
/*
* Filename: listener.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Listener implementation
* Instruction:
*/

#include "listener.hpp"

/*
*
*/
Listener::Listener(std::string t_hostname, std::string t_port)
{
  this->hostname = t_hostname;
  this->port = t_port;
}

/*
*
*/
Listener::~Listener()
{
  close(this->listener_sock);
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
  if ((rv = getaddrinfo(this->hostname.c_str(), this->port.c_str(), &hints, &myinfo)) != 0) {
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

  if(!this->set_sock_nonblocking(true))
  {
      perror("set_sock_nonblocking()");
      throw std::runtime_error("set_sock_nonblocking()");
  }

  if (listen(sockfd, LISTENER_MAX_LISTEN_BACKLOG) == -1) {
    perror("listen()");
    throw std::runtime_error("listen()");
  }

  this->listener_sock = sockfd;
}

/*
*
*/
int Listener::get_listener_sock()
{
  return this->listener_sock;
}



/*
*
*/
std::vector<int> Listener::get_accept_socks()
{
  std::vector<int> output;
  while(true)
  {
    int their_sock = accept(this->mysock, their_addr, sin_size);
    if (their_sock < 0)
    {
      break;
    }
    output.push_back(their_sock);
  }
  return output;
}


/*
*
*/
bool Listener::set_sock_nonblocking(bool non_blocking)
{
  if (sock < 0){return false;}
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {return false;}
  flags = non_blocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
  return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
}
