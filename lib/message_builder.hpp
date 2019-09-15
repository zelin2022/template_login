/*
* Filename: message_builder.hpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/
#ifndef _MESSAGE_BUILDER_HPP_
#define _MESSAGE_BUILDER_HPP_
class Message_builder
{
public:
  Message_builder();
  ~Message_builder();
  static std::shared_ptr<Message> create_message_sign_up_success();
  static std::shared_ptr<Message> create_message_sign_up_failed();
  static std::shared_ptr<Message> create_message_sign_in_success();
  static std::shared_ptr<Message> create_message_sign_in_failed();
private:

};
#endif
