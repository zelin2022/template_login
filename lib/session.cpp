/*
* Filename: session.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Session implementation
* Instruction:
*/
#include "session.hpp"


/*
* constructor
*/
Session::Session(int sock)
{
  if(sock < 0){
    throw std::runtime_error("Session created with bad socket value : " + std::to_string(sock));
  }
  this->mysock = sock;
  this->is_closed = false;
  this->incomplete_msg = std::make_shared<Message>(SESSION_STANDARD_MSG_LEN);
}

/*
*
*/
void Session::do_session()
{
  // if this function is called, then there is data on fd's rx buffer
  this->recv_all_msg();

  while(!this->complete_msgs.empty())
  {
    this->process_one_msg();
    this->complete_msgs.pop();
  }
}

/*
*
*/
void Session::recv_all_msg()
{//

  while(true)
  {
    ssize_t len_to_recv = SESSION_STANDARD_MSG_LEN - this->incomplete_msg.get()->cur_len;
    ssize_t actual_recv_len = this->receive(this->incomplete_msg.data + this->incomplete.cur_len, len_to_recv);
    if(len_to_recv > actual_recv_len )
    {
      if(actual_recv_len > 0)
      {// recv returns a value
        this.incomplete_msg.get()->cur_len += actual_recv_len;
      }
      break;
    }
    else // incomplete_msg is finished_msg
    {
      this->complete_msgs.push(std::move(this->incomplete_msg));
      this->incomplete_msg = std::make_shared<Message>(SESSION_STANDARD_MSG_LEN);
    }

  }
}

/*
*
*/
void Session::process_one_msg()
{
  char type = this->complete_msgs.front().get()->data[0];
  switch(type)
  {
    case SESSION_MSG_INDEX_SIGNIN:
    case SESSION_MSG_INDEX_SIGNUP:
    default:
    throw std::runtime_error("MSG INDEX DOES NOT MATCH ANY EXISTING INDEX");
  }
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
