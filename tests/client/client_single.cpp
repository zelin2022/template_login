/*
* Filename: cllient_single.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description:
* Instruction:
*/

#include <iostream>
#include <memory>
#include <cstring>

#include "tcp_socket.hpp"

#define MESSAGE_CODE_SIGN_UP_REQUEST 0xf004
#define MESSAGE_DIVIDER_EOT 0x04
#define MESSAGE_DIVIDER_ETX 0x03


class Message_body{
public:
  Message_body(int t_len):m_len(t_len)
  {
    this->m_data = (char*)malloc(sizeof(char)*t_len);
  }
  ~Message_body()
  {
    if(this->m_data)
    {
      free(m_data);
    }
  }
  char* m_data;
  short m_len;
};

std::shared_ptr<Message_body> create_test_signin(std::string t_username, std::string t_password)
{
  short len = 2+2+t_username.size()+1+2+t_password.size()+1+1;
  std::shared_ptr<Message_body> output = std::make_shared<Message_body>(len);

  short cur_len = 0;
  char c_EOT = MESSAGE_DIVIDER_EOT;
  char c_ETX = MESSAGE_DIVIDER_ETX;

  short message_code = MESSAGE_CODE_SIGN_UP_REQUEST;
  memcpy(output->m_data+cur_len, &message_code, 2);
  cur_len += 2;


  short username_len = t_username.size();
  memcpy(output->m_data+cur_len, &username_len, 2);
  cur_len += 2;

  memcpy(output->m_data+cur_len, t_username.c_str(), username_len);
  cur_len += username_len;

  memcpy(output->m_data+cur_len, &c_ETX, 1);
  cur_len += 1;

  short password_len = t_password.size();
  memcpy(output->m_data+cur_len, &password_len, 2);
  cur_len += 2;

  memcpy(output->m_data+cur_len, t_password.c_str(), password_len);
  cur_len += password_len;

  memcpy(output->m_data+cur_len, &c_ETX, 1);
  cur_len += 1;

  memcpy(output->m_data+cur_len, &c_EOT, 1);
  cur_len += 1;

  if (cur_len != len)
  {
    std::cout<<"wrong len"<<std::endl;
  }
  return output;




}

int main(int argc, char** argv)
{
  if(argc != 5){
    std::cout<< "wrong argc\n";
    return -1;
  }
   std::shared_ptr<TCP_Socket> tcp = std::make_shared<TCP_Socket>(false, argv[1], argv[2], argv[3], argv[4]);
   std::shared_ptr<Message_body> to_send_signup = create_test_signin(
     std::string("Zelin"),
     std::string("love)")
   );
   tcp->write((void*)&(to_send_signup->m_len), 2);
   tcp->write(to_send_signup->m_data, to_send_signup->m_len);


}
