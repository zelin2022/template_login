/*
* Filename: Message_body.cpp
* Author: Zelin Liu
* Date: 2019/09/08
* Description:
* Instruction:
*/

#include "Message_body.hpp"

Message_body::Message_body(int len)
{
  this->data_len = len;
  this->data = (char*)malloc(this->data_len * sizeof(char));
  this->cur_len = 0;
}



~Message_body::Message_body()
{
  if(this->data != NULL){
    free(this->data);
  }
}


bool Message_body::filled()
{
  if(this-> data_len > this->cur_len)
  {
    return false;
  }
  else if (this-> data_len == this-> cur_len)
  {
    return true;
  }
  else
  {
    throw std::runtime_error("Message_body: cur_len > data_len");
  }
  return false;
}
