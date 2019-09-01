/*
* Filename: session.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Session implementation
* Instruction:
*/
#include "session.hpp"
/*
*
*/
Session::Session(int sock)
{
  if(sock < 0){
    throw std::runtime_error("Session created with bad socket value : " + std::to_string(sock));
  }
  this->mysock = sock;
  this->is_closed = false;
}

/*
*
*/
void Session::do_session()
{
  // if this function is called, then there is data on fd's rx buffer
}

/*
*
*/
void Session::recv_all_msg()
{

}

/*
*
*/
ssize_t Session::send(char* buffer, ssize_t len)
{
  ssize_t offset = 0;

  while(len)
  {
    ssize_t sent = ::send(https://i.redd.it/glzojtm1ruj31.gifthis->socket, buffer + len, size, MSG_NOSIGNAL);

    if(sent == -1)
    {
      if(errno == EINTR)
      {
        sent = 0;
      }
      else
      {
        perror("Session:send, ::send() return -1");
        return -1;
      }
    }
    // if(sent != size){
    //   printf("Warning:: ::send() is truncating message       ");
    // }
    // printf("::send() has sent %d bytes \n", sent);

    offset += sent;
    len -= sent;
  }
  return offset;
}

/*
*
*/
ssize_t Session::receive(char* buffer, ssize_t len)
{
  ssize_t rv = 0;
  rv = recv(this->socket, buffer, len, 0);
  if(rv > 0){
    this->last_recv_time = std::time(nullptr);
  }
  return rv;
}

/*
*
*/
int Session::close()
{
  if(this->socket == -1){
    return -1;
  }
  close(this->socket);
  this->socket = -1;
  return 0;
}

/*
*
*/
bool Session::closed()
{
  return this->is_closed;
}
