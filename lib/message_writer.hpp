/*
* Filename: message_writer.hpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/
#ifndef _MESSAGE_WRITER_HPP_
#define _MESSAGE_WRITER_HPP_
#include <memory>
#include <deque>
#include "message_body.hpp"
// #include <sys/types.h>
#include <sys/socket.h>

class Message_writer
{
public:
  Message_writer(int sock);
  ~Message_writer();
  void write_all(std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> in);
  ssize_t write(char* buffer, size_t len);
  ssize_t write_message(std::shared_ptr<Message_body> message);
private:
  ssize_t sendall(char *buf, int* len);
  int socket;

};
#endif
