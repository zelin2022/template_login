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
#include <sys/socket.h>

class Message_body;

class Message_writer
{
public:
  Message_writer(int t_socket);
  ~Message_writer();
  void write_all(std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> t_in_queue);
  ssize_t write(char* t_buffer, size_t t_len);
  ssize_t write_message(std::shared_ptr<Message_body> t_message);
private:
  ssize_t sendall(char *t_buf, int* t_len);
  int m_socket;

};
#endif
