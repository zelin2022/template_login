/*
* Filename: message_body.hpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/
#ifndef _MESSAGE_BODY_HPP_
#define _MESSAGE_BODY_HPP_
class Message_body{
public:
  Message_body(int len);
  ~Message_body();

  bool filled();

  char* data;
  unsigned short data_len;
  unsigned short cur_len;
};
#endif
