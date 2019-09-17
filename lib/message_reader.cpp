/*
* Filename: message_reader.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "message_reader.hpp"

/*
*
*/
Message_reader::Message_reader(std::shared_ptr<std::time_t> last_recv_time, int sock)
{
  this->last_recv_time = last_recv_time;
  this->socket = sock;
  header = std::make_unique<Message_header>();
  body = nullptr;
  this->expect_to_read_EOT = false;
}

/*
*
*/
Message_reader::~Message_reader()
{
}

/*
*
*/
std::vector<std::shared_ptr<Message_body>> Message_reader::read_all()
{
  std::vector<std::shared_ptr<Message_body>> output;
  // while there is data in rx buffer to read
  while(true)
  {
    if(this->body == nullptr)
    {
      if(this->expect_to_read_EOT)
      {
          char eot_temp;
          this->read(&eot_temp, 1);
          if(eot_temp != MESSAGE_DIVIDER_EOT)
          {
            throw std::runtime_error("EOT [" + std::to_string(MESSAGE_DIVIDER_EOT) + "] expected, but got [" + std::to_string(eot_temp) + "] instead");
          }
          else
          {
            this->expect_to_read_EOT = false;
          }
      }
      ssize_t returned_len = this->read(
        this->header->header + this->header->received_message_header_len,
        MESSAGE_HEADER_LEN - this->header->received_message_header_len
      );
      if(returned_len <= 0 )
      {
        break;
      }
      this->header->received_message_header_len += returned_len;
      if(this-> header->received_message_header_len = MESSAGE_HEADER_LEN)
      {
          this->body = this->header->create_body_and_reset();
      }
    }
    else
    {
      ssize_t returned_len = this->read(
        this->body->data + this->body->cur_len,
        this->body->data_len - this->body->cur_len
      );
      if(returned_len <= 0)
      {
        break;
      }
      this->body->cur_len += returned_len;
      if(this->body->filled())
      {
        this->expect_to_read_EOT = true;
        output.push_back(std::move(this->body));
        this->body = nullptr;
      }
    }
  }
  return output;
}

/*
*
*/
ssize_t Message_reader::read(char* buffer, ssize_t len)
{
  ssize_t rv = 0;
  rv = ::recv(this->socket, buffer, len, 0);
  if(rv > 0){
    *this->last_recv_time = std::time(nullptr);
  }
  return rv;
}
