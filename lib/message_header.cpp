/*
* Filename: message_header.cpp
* Author: Zelin Liu
* Date: 2019/09/11
* Description:
* Instruction:
*/

#include "message_header.hpp"

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
*
*/
std::shared_ptr<Message_body> Message_header::create_body_and_reset()
{

  unsigned short temp  = this->received_message_header_len;
  this->received_message_header_len = 0;

  return std::make_shared<Message_body>(temp); 
}
