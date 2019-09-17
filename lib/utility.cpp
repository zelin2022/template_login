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


  unsigned short len_username = Message_processor::binary_2_ushort(data);
  username = std::string(data+2, (size_t)len_username);
  unsigned char expected_ETX = data[2+len_username];
  if(expected_ETX != HEX_END_OF_TEXT)
  {
    throw std::runtime_error("username ETX [" + std::to_string(HEX_END_OF_TEXT) + "] expected, but got [" + std::to_string(expected_ETX) + "] instead");
  }
  unsigned char len_password =Message_processor::binary_2_ushort(data+2+len_username+1);
  password = std::string(data+2+len_username+1+2, (size_t)len_password);
  expected_ETX = data[data+2+len_username+1+2+len_password];
  if(expected_ETX != HEX_END_OF_TEXT)
  {
    throw std::runtime_error("password ETX [" + std::to_string(HEX_END_OF_TEXT) + "] expected, but got [" + std::to_string(expected_ETX) + "] instead");
  }


}

/*
*
*/
unsigned short Utility::binary_2_ushort(char * data)
{
  return (unsigned short) ((data[1] << 8) &0xFF00) | (data[0]) ;
}
