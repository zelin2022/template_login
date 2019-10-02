/*
* Filename: Message_body.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "message_body.hpp"
#include <stdlib.h>
#include <stdexcept>

Message_body::Message_body(int t_len)
: m_data_len(t_len)
{

  this->m_data = (char*)malloc(this->m_data_len * sizeof(char));
  this->m_cur_len = 0;
}



Message_body::~Message_body()
{
  if(this->m_data != NULL){
    free(this->m_data);
  }
}


bool Message_body::filled()
{
  if(this-> m_data_len > this->m_cur_len)
  {
    return false;
  }
  else if (this-> m_data_len == this-> m_cur_len)
  {
    return true;
  }
  else
  {
    throw std::runtime_error("Message_body: m_cur_len > m_data_len");
  }
  return false;
}
