/*
* Filename: utility.hpp
* Author: Zelin Liu
* Date: 2019/09/17
* Description:
* Instruction:
*/
#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_
#include <string>
#include <stdexcept>
#include "message_code.h"

class Utility
{
public:
  static unsigned short binary_2_ushort(char * t_data);
  static void get_username_and_password(char* t_data, std::string &t_username, std::string &t_password);
};
#endif
