/*
* Filename: message_reader.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "message_reader.hpp"

#include "message_body.hpp"
#include "message_header.hpp"
#include <sys/socket.h>



/*
*
*/
Message_reader::Message_reader(std::shared_ptr<std::time_t> t_last_recv_time, int t_socket)
:m_socket(t_socket), m_last_recv_time(t_last_recv_time)
{

  m_header = std::make_unique<Message_header>();
  m_body = nullptr;

}

/*
*
*/
Message_reader::~Message_reader()
{
}




/*
 all the possible challenges here:
 the most concern is that this function doesn't handle unfinished messages and run-on messages well

 two states : reading header and reading body.

 unfinished len.

 when a read returns, update the two values accordingly.

 when enterying this function, make sure enter at the approriate point
*/
std::vector<std::shared_ptr<Message_body>> Message_reader::read_all()
{
  std::vector<std::shared_ptr<Message_body>> output;
  while(true)
  {
    // enter loop reading header
    if(this->m_body == nullptr)
    {
      ssize_t returned_len = this->read(
        this->m_header->header + this->m_header->received_message_header_len,
        MESSAGE_HEADER_LEN - this->m_header->received_message_header_len
      );

      if(returned_len <= -1)
      {
        break;
      }

      this->m_header->received_message_header_len += returned_len;
      if(this->m_header->received_message_header_len < MESSAGE_HEADER_LEN)
      {
        break;
      }
      else if (this->m_header->received_message_header_len == MESSAGE_HEADER_LEN)
      {
        this->m_body = this->m_header->create_body_and_reset();
      }
      else
      {
        throw std::runtime_error("received_message_header_len > MESSAGE_HEADER_LEN");
      }

    }
    // enter loop reading body
    else
    {
      ssize_t returned_len = this->read(
        this->m_body->m_data + this->m_body->m_cur_len,
        this->m_body->m_data_len - this->m_body->m_cur_len
      );
      if(returned_len <= 0)
      {
        break;
      }
      this->m_body->m_cur_len += returned_len;
      if(this->m_body->filled())
      {
        output.push_back(std::move(this->m_body));
        this->m_body = nullptr;
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
  rv = ::recv(this->m_socket, buffer, len, 0);
  if(rv > 0){
    *this->m_last_recv_time = std::time(nullptr);
  }
  return rv;
}
