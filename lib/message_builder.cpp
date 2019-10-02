/*
* Filename: message_builder.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "message_builder.hpp"
#include "message_body.hpp"
#include <cstring>

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
  memcpy(output->m_data+created, &code, 2);
  created += 2;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy(output->m_data+created, &EOT, 1);

  return output;
}

std::shared_ptr<Message_body> Message_builder::create_message_sign_up_failed(std::string result)
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+result.size()+1+1);

  unsigned short code = MESSAGE_CODE_SIGN_UP_FAILURE;
  memcpy(output->m_data+created, &code, 2);
  created += 2;

  unsigned short tx_len = result.size();
  memcpy(output->m_data+created, &tx_len, 2);
  created += 2;

  memcpy(output->m_data+created, result.c_str(), result.size());
  created += result.size();

  char ETX = MESSAGE_DIVIDER_ETX;
  memcpy(output->m_data+created, &ETX, 1);
  created += 1;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy(output->m_data+created, &EOT, 1);

  return output;
}

std::shared_ptr<Message_body> Message_builder::create_message_sign_in_success(std::string result)
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+result.size()+1+1);

  unsigned short code = MESSAGE_CODE_SIGN_IN_SUCCESS;
  memcpy(output->m_data+created, &code, 2);
  created += 2;

  unsigned short tx_len = result.size();
  memcpy(output->m_data+created, &tx_len, 2);
  created += 2;

  memcpy(output->m_data+created, result.c_str(), result.size());
  created += result.size();

  char ETX = MESSAGE_DIVIDER_ETX;
  memcpy(output->m_data+created, &ETX, 1);
  created += 1;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy(output->m_data+created, &EOT, 1);

  return output;
}

std::shared_ptr<Message_body> Message_builder::create_message_sign_in_failed(std::string result)
{
  unsigned short created = 0;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(2+result.size()+1+1);

  unsigned short code = MESSAGE_CODE_SIGN_IN_FAILURE;
  memcpy(output->m_data+created, &code, 2);
  created += 2;

  unsigned short tx_len = result.size();
  memcpy(output->m_data+created, &tx_len, 2);
  created += 2;

  memcpy(output->m_data+created, result.c_str(), result.size());
  created += result.size();

  char ETX = MESSAGE_DIVIDER_ETX;
  memcpy(output->m_data+created, &ETX, 1);
  created += 1;

  char EOT = MESSAGE_DIVIDER_EOT;
  memcpy(output->m_data+created, &EOT, 1);

  return output;
}
