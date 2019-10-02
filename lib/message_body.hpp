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
  Message_body(int t_len);
  ~Message_body();

  bool filled();

  char* m_data;
  unsigned short m_data_len;
  unsigned short m_cur_len;
};
#endif
