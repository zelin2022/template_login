/*
* Filename: tcp_socket.cpp
* Author: Zelin Liu
* Date: 2019/09/30
* Description:
* Instruction:
*/

#include "tcp_socket.hpp"

/*
*
*/
TCP_Socket::TCP_Socket(bool t_is_server, char* t_my_ip, char* t_my_port, char* t_their_ip, char* t_their_port)
:m_is_server(t_is_server)
{
  this->m_socket = this->SocketSetup(t_my_ip, t_my_port);

  if(!t_is_server)
  {
    this->connect(this->m_socket, t_their_ip, t_their_port);
  }

}

/*
*
*/
bool TCP_Socket::write(void *t_buffer, int t_len)
{
  int total = 0;        // how many bytes we've sent
  int bytesleft = t_len; // how many we have left to send
  int n;

  while(total < t_len) {
      n = ::send(this->m_socket, t_buffer+total, bytesleft, 0);
      if (n == -1) { break; }
      total += n;
      bytesleft -= n;
  }

  // t_len = total; // return number actually sent here

  return n==-1?false:true; // return -1 on failure, 0 on success

}


/*
*
*/
ssize_t TCP_Socket::read(char* t_buffer, ssize_t t_len)
{
  ssize_t rv = 0;
  rv = ::recv(this->m_socket, t_buffer, t_len, 0);
  if(rv > 0){
    // *this->last_recv_time = std::time(nullptr);
  }
  return rv;
}

void TCP_Socket::exit()
{
  ::close(this->m_socket);
}

/*
*
*/
int TCP_Socket::SocketSetup(char* t_my_ip, char* t_my_port)
{
  int sockfd;
  struct addrinfo hints, *myinfo, *p;
  memset(&hints, 0, sizeof (hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP

  int rv;
  if ((rv = getaddrinfo(t_my_ip, t_my_port, &hints, &myinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return -1;
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
    fprintf(stderr, "my addr: failed\n");
    return(-1);
  }
  return sockfd;
}

/*
*
*/
int TCP_Socket::connect(int socket, char* t_their_ip, char* t_their_port)
{
  struct addrinfo hints, *theirinfo, *p;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int rv;
  if ((rv = getaddrinfo(t_their_ip, t_their_port, &hints, &theirinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return -1;
  }
  for (p = theirinfo; p != NULL; p=p->ai_next){
    if (::connect(socket, p->ai_addr, p->ai_addrlen) == -1) {
      close(socket);
      perror("client: connect");
      return -1;
    }
    break;
  }
  return 0;
}
