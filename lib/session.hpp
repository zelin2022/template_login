/*
* Filename: session.hpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: TLS_Session definition
* Instruction:
*/
#ifndef _SESSION_HPP_
#define _SESSION_HPP_
#include <cstring>
class Message
{
public:
  Message(int len)
  {
    this->max_len = len;
    this->data = (char*) malloc( sizeof(char)* len );
    this->cur_len = 0;
  }
  ~Message()
  {
    free(this->data);
  }
  char* data;
  int max_len;
  int cur_len
};

class Session{
public:
  Session(int sock);
  void do_session();

  int close();
  ~Session();
private:
  void recv_msg();
  ssize_t send(char* buffer, ssize_t len);
  ssize_t receive(char* buffer, ssize_t* len);

  std::vector<std::shared__ptr<Message>> complete_msgs;
  std::shared_ptr<Message> unfinished_msg;

  int mysock;
  std::time_t last_recv_time;
  bool is_closed;
};
#endif
