/*
* Filename: utility.hpp
* Author: Zelin Liu
* Date: 2019/09/17
* Description:
* Instruction:
*/
#include "utility.hpp"
/*
*
*/
void Utility::get_username_and_password(char* data, std::string &username, std::string &password)
{
  unsigned short parsed = 0;

  unsigned short len_username = Utility::binary_2_ushort(data);
  parsed += 2;
  username = std::string(data+parsed, (size_t)len_username);
  parsed += len_username;
  unsigned char expected_ETX = data[parsed];
  if(expected_ETX != MESSAGE_DIVIDER_ETX)
  {
    throw std::runtime_error("username ETX [" + std::to_string(MESSAGE_DIVIDER_ETX) + "] expected, but got [" + std::to_string(expected_ETX) + "] instead");
  }
  parsed+=1;
  unsigned char len_password =Utility::binary_2_ushort(data+parsed);
  parsed+=2;
  password = std::string(data+parsed, (size_t)len_password);
  parsed+=len_password;
  expected_ETX = data[parsed];
  if(expected_ETX != MESSAGE_DIVIDER_ETX)
  {
    throw std::runtime_error("password ETX [" + std::to_string(MESSAGE_DIVIDER_ETX) + "] expected, but got [" + std::to_string(expected_ETX) + "] instead");
  }


}

/*
*
*/
unsigned short Utility::binary_2_ushort(char * data)
{
  return (unsigned short) ((data[1] << 8) &0xFF00) | (data[0]) ;
}
