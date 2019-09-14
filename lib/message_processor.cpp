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
Message_processor::Message_processor(std::shared_ptr<DB_core> db)
{
    this->db_core = db;
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
    case MESSAGE_CODE_SIGN_UP:
    this->do_sign_up(msg);
    case MESSAGE_CODE_SIGN_IN:
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

}

/*
*
*/
void do_sign_in(std::shared_ptr<Message_body> msg)
{

}

/*
*
*/
static void get_username_and_password(char* data, std::string &username, std::string &password)
{
  // to understand what's going on here we need to understand message sturcture
  ///////////////////////////////////////////
  // header  2 bytes
    ///////////////////////////////////////////
    // body
    // message code 2bytes
    ///////////////////////////////////////////
    // Length of username 1 byte
      ///////////////////////////////////////////
      // username n bytes
    // ETX 1 byte
    ///////////////////////////////////////////
    // Length of password 1 byte
      ///////////////////////////////////////////
      // password n bytes
    // ETX 1 byte
  ///////////////////////////////////////////
  // EOT 1 byte
  ///////////////////////////////////////////



  unsigned char len_username = data[0];
  username = std::string(data+1, (size_t)len_username);
  unsigned char expected_ETX = data[1+len_username];
  if(expected_ETX != HEX_END_OF_TEXT)
  {
    throw std::runtime_error("username ETX [" + std::to_string(HEX_END_OF_TEXT) + "] expected, but got [" + std::to_string(expected_ETX) + "] instead");
  }
  unsigned char len_password = data[1+len_username+1];
  password = std::string(data+1+len_username+1+1, (size_t)len_password);
  expected_ETX = data[data+1+len_username+1+1+len_password];
  if(expected_ETX != HEX_END_OF_TEXT)
  {
    throw std::runtime_error("password ETX [" + std::to_string(HEX_END_OF_TEXT) + "] expected, but got [" + std::to_string(expected_ETX) + "] instead");
  }


}
