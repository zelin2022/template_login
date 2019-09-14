/*
* Filename: message_reader.hpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#ifndef _MESSAGE_READER_HPP_
#define _MESSAGE_READER_HPP_

class Message_reader
{
public:
  Message_reader(std::shared_ptr<std::time_t> last_recv_time, int sock);
  ~Message_reader();
  std::vector<std::shared_ptr<Message>> read_all;
private:

  ssize_t read(char* buffer, ssize_t len);
  int socket;
  std::shared_ptr<std::time_t> last_recv_time
  std::unique_ptr<Message_header> header;
  std::shared_ptr<Message_body> body;
  bool expect_to_read_EOT;
};
#endif
