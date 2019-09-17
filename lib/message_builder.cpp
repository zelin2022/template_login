/*
* Filename: message_builder.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "message_builder.hpp"

Message_builder::Message_builder()
{

}

Message_builder::~Message_builder()
{

}

/*
*
*/
std::shared_ptr<Message_body> Message_builder::create_message_sign_up_success()
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+1);

  unsigned short code = MESSAGE_CODE_SIGN_UP_SUCCESS;
  memcpy_s(output->data+created, output->cur_len-created, &code, 2);
  created += 2;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy_s(output->data+created, coutput>cur_len-created, &EOT, 1);

  return output;
}

std::shared_ptr<Message_body> Message_builder::create_message_sign_up_failed(std::string result)
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+result.size()+1+1);

  unsigned short code = MESSAGE_CODE_SIGN_UP_FAILURE;
  memcpy_s(output->data+created, output->cur_len-created, &code, 2);
  created += 2;

  memcpy_s(output->data+created, output->cur_len-created, result.c_str(), result.size());
  created += result.size();

  char ETX = MESSAGE_DIVIDER_ETX;
  memcpy_s(output->data+created, output->cur_len-created, &ETX, 1);
  created += 1;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy_s(output->data+created, output->cur_len-created, &EOT, 1);

  return output;
}

std::shared_ptr<Message_body> Message_builder::create_message_sign_in_success(std::string result)
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+result.size()+1+1);

  unsigned short code = MESSAGE_CODE_SIGN_IN_SUCCESS;
  memcpy_s(output->data+created, output->cur_len-created, &code, 2);
  created += 2;

  memcpy_s(output->data+created, output->cur_len-created, result.c_str(), result.size());
  created += result.size();

  char ETX = MESSAGE_DIVIDER_ETX;
  memcpy_s(output->data+created, output->cur_len-created, &ETX, 1);
  created += 1;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy_s(output->data+created, output->cur_len-created, &EOT, 1);

  return output;
}

std::shared_ptr<Message_body> Message_builder::create_message_sign_in_failed(std::string result)
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+result.size()+1+1);

  unsigned short code = MESSAGE_CODE_SIGN_IN_FAILURE;
  memcpy_s(output->data+created, output->cur_len-created, &code, 2);
  created += 2;

  memcpy_s(output->data+created, output->cur_len-created, result.c_str(), result.size());
  created += result.size();

  char ETX = MESSAGE_DIVIDER_ETX;
  memcpy_s(output->data+created, output->cur_len-created, &ETX, 1);
  created += 1;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy_s(output->data+created, output->cur_len-created, &EOT, 1);

  return output;
}
