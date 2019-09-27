/*
* Filename: message_processor.cpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/

#include "message_processor.hpp"

/*
*
*/
Message_processor::Message_processor(std::shared_ptr<DB_con> dbcon, std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> queue)
{
    this->db = dbcon;
    this->send_queue= send_queue;
}

/*
*
*/
Message_processor::~Message_processor()
{

}

/*
*
*/
void Message_processor::process_messages(std::vector<std::shared_ptr<Message_body>> input)
{
 for (int i = 0; i<input.size(); i++)
 {
   this->process_one_msg(input[i]);
 }
}


/*
*
*/
void Message_processor::process_one_msg(std::shared_ptr<Message_body> msg)
{
  unsigned short msg_code = Utility::binary_2_ushort(msg->data);
  switch(msg_code)
  {
    case MESSAGE_CODE_SIGN_UP_REQUEST:
    this->do_sign_up(msg);
    case MESSAGE_CODE_SIGN_IN_REQUEST:
    this->do_sign_in(msg);
    default:
    throw std::runtime_error("Message code [" + std::to_string(msg_code) + "] does not match any known code");
  }
}


/*
*
*/
void Message_processor::do_sign_up(std::shared_ptr<Message_body> msg)
{
  std::string username;
  std::string password;
  Utility::get_username_and_password(msg->data+2, username, password);
  std::string SQL("INSERT into user (USERNAME, PASSWORD, DATA) VALUES ('"+ username +"', '"+password+"', '22')");
  try{
    this->db->exec(SQL);
    // send success msg
    this->send_queue->push_back(Message_builder::create_message_sign_up_success());
  }catch(std::runtime_error &e){
    // send failed msg
    this->send_queue->push_back(Message_builder::create_message_sign_up_failed(this->db->get_last_error()));
  }

}

/*
*
*/
void Message_processor::do_sign_in(std::shared_ptr<Message_body> msg) // password sign in
{
  std::string username;
  std::string password;
  Utility::get_username_and_password(msg->data+2, username, password);
  std::string SQL("SELECT DATA from user where USERNAME = '"+ username +"' and PASSWORD = '" + password + "'");
  try{
    this->db->exec(SQL);
    // return success MSG
    this->send_queue->push_back(Message_builder::create_message_sign_in_success(this->db->get_last_error()));

  }catch(std::runtime_error &e){
    // return failed MSG
    this->send_queue->push_back(Message_builder::create_message_sign_in_failed(this->db->get_last_error()));
  }
}
