/*
* Filename: message_header.cpp
* Author: Zelin Liu
* Date: 2019/09/11
* Description:
* Instruction:
*/

#include "message_header.hpp"
#include "utility.hpp"
#include "message_body.hpp"
#include <stdexcept>

/*
*
*/
Message_header::Message_header()
{
  this->received_message_header_len = 0;
}

/*
*
*/
Message_header::~Message_header()
{

}

/*
* make sure you check received_message_header_len first
*/
std::shared_ptr<Message_body> Message_header::create_body_and_reset()
{
  // if(this->received_message_header_len != MESSAGE_HEADER_LEN)
  // {
  //   return nullptr;
  // }
  unsigned short temp  = Utility::binary_2_ushort(this->header);
  this->received_message_header_len = 0;

  return std::make_shared<Message_body>(temp);
}
