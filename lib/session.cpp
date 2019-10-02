/*
* Filename: session.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Session implementation
* Instruction:
*/
#include "session.hpp"
#include "db_con.hpp"
#include "message_reader.hpp"
#include "message_writer.hpp"
#include "message_body.hpp"
#include "message_processor.hpp"
#include <cstring>


/*
* constructor
*/
Session::Session(int t_socket, std::shared_ptr<DB_con> t_db)
:m_socket(t_socket), m_db(std::move(t_db))
{
  if(t_socket < 0){
    throw std::runtime_error("Session created with bad socket value : " + std::to_string(t_socket));
  }
  // this->m_mysock = sock;
  // this->m_is_closed = false;
  // this->m_incomplete_msg = std::make_shared<Message>(SESSION_STANDARD_MSG_LEN);
  this->m_last_recv_time = std::make_shared<std::time_t>();
  this->m_reader = std::make_unique<Message_reader>(this->m_last_recv_time, this->m_socket);
  this->m_writer = std::make_unique<Message_writer>(this->m_socket);
  this->m_to_send = std::make_shared<std::deque<std::shared_ptr<Message_body>>>();
  this->m_processor = std::make_unique<Message_processor>(this->m_db, this->m_to_send);
  // this->m_db_con = db;

}

/*
*
*/
Session::~Session()
{

}

/*
*
*/
void Session::do_session()
{
  // // if this function is called, then there is data on fd's rx buffer
  // this->m_recv_all_msg();
  //
  // while(!this->m_complete_msgs.empty())
  // {
  //   this->m_process_one_msg();
  //   this->m_complete_msgs.pop();
  // }



  std::vector<std::shared_ptr<Message_body>> recvd_msg = this->m_reader->read_all();
  this->m_processor->process_messages(recvd_msg);
  this->m_writer->write_all(this->m_to_send);

}
