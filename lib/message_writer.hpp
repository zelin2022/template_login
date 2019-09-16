/*
* Filename: message_writer.hpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/
#ifndef _MESSAGE_WRITER_HPP_
#define _MESSAGE_WRITER_HPP_
class
{
public:
  Message_writer(int sock);
  ~Message_writer();
private:
  ssize_t write(char* buffer, size_t len);
  void write_message(std::shared_ptr<Message_body> message);
  int socket;

};
#endif
