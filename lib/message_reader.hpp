/*
* Filename: message_reader.hpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#ifndef _MESSAGE_READER_HPP_
#define _MESSAGE_READER_HPP_


#include "macro.h"
#include <ctime>

#include <vector>
#include <memory>

class Message_body;
class Message_header;


class Message_reader
{
public:
  Message_reader(std::shared_ptr<std::time_t> t_last_recv_time, int t_socket);
  ~Message_reader();
  std::vector<std::shared_ptr<Message_body>> read_all();
private:

  ssize_t read(char* buffer, ssize_t len);
  int m_socket;
  std::shared_ptr<std::time_t> m_last_recv_time;


  std::unique_ptr<Message_header> m_header;
  std::shared_ptr<Message_body> m_body;
};
#endif
