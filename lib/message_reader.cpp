/*
* Filename: message_reader.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "message_read.hpp"

/*
*
*/
Message_reader::Message_reader(std::shared_ptr<std::time_t> last_recv_time, int sock)
{
  this->last_recv_time = last_recv_time;
  this->socket = sock
  header = std::make_unique<Message_header>();
  body = nullptr
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
std::vector<std::shared_ptr<Message>> Message_reader::read_all()
{
  std::vector<std::shared_ptr<Nessage>> output;
  // while there is data in rx buffer to read
  while(true)
  {
    if(this->body == nullptr)
    {
      ssize_t returned_len = this->read(
        this->header.get()->header + this->header.get()->received_message_header_len,
        MESSAGE_HEADER_LEN - this->header.get()->received_message_header_len
      );
      if(returned_len <= 0 )
      {
        break;
      }
      this->header.get()->received_message_header_len += returned_len;
      if(this-> header.get()->received_message_header_len = MESSAGE_HEADER_LEN)
      {
          this->body = this->header.get()->create_body_and_reset();
      }
    }
    else
    {
      ssize_t returned_len = this->read(
        this->body.get()->data + this->body.get()->cur_len,
        this->body.get()->data_len - this->body.get()->cur_len;
      );
      if(returned_len <= 0)
      {
        break;
      }
      this->body.get()->cur_len += returned_len;
      if(this->body.get()->filled())
      {
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
  rv = recv(this->socket, buffer, len, 0);
  if(rv > 0){
    this->last_recv_time = std::time(nullptr);
  }
  return rv;
}
