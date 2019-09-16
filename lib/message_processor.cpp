/*
* Filename: message_processor.cpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/

/*
*
*/
Message_processor::Message_processor(std::shared_ptr<DB_core> db, std::shared_ptr<std::deque<std::shared_ptr<Message>>> queue)
{
    this->db_core = db;
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
  unsigned short msg_code = this->binary_2_ushort(msg.get().data);
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
unsigned short Message_processor::binary_2_ushort(char * data)
{
  return (unsigned short) ((data[1] << 8) &0xFF00) | (data[0]) ;
}

/*
*
*/
void do_sign_up(std::shared_ptr<Message_body> msg)
{
  std::string username;
  std::string password;
  this->get_username_and_password(msg.get().data+2, username, password);
  std::string SQL("INSERT into user (USERNAME, PASSWORD, DATA) VALUES ('"+ username +"', '"+password+"', '22')");
  try{
    this->db->exec(SQL);
    // send success msg
    this->send_queue.get().push_back(Message_builder::create_message_sign_up_success(this->db.get_last_error()));
  }catch(std::runtime_error &e){
    // send failed msg
    this->send_queue.get().push_back(Message_builder::create_message_sign_up_failed(this->db.get_last_error()));
  }

}

/*
*
*/
void do_sign_in(std::shared_ptr<Message_body> msg) // password sign in
{
  std::string username;
  std::string password;
  this->get_username_and_password(msg.get().data+2, username, password);
  std::string SQL("SELECT DATA from user where USERNAME = '"+ username +"' and PASSWORD = '" + password + "'");
  try{
    this->db->store(SQL, (int)123);
    // return success MSG
    this->send_queue.get().push_back(Message_builder::create_message_sign_in_success());

  }catch(std::runtime_error &e){
    // return failed MSG
    this->send_queue.get().push_back(Message_builder::create_message_sign_in_failed(this->db.get_last_error()));
  }
}

/*
*
*/
void get_username_and_password(char* data, std::string &username, std::string &password)
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
