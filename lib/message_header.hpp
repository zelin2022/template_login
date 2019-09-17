/*
* Filename: message_header.hpp
* Author: Zelin Liu
* Date: 2019/09/11
* Description:
* Instruction:
*/

#ifndef _MESSAGE_HEADER_HPP_
#define _MESSAGE_HEADER_HPP_

#include "macro.h"
#include "message_body.hpp"
#include "message_processor.hpp"
#include <memory>

class Message_header
{
public:
  Message_header();
  ~Message_header();
  char header[MESSAGE_HEADER_LEN];
  unsigned short received_message_header_len;
  std::shared_ptr<Message_body> create_body_and_reset();
};

#endif
