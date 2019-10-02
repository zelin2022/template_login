/*
* Filename: session.hpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: TLS_Session definition
* Instruction:
*/
#ifndef _SESSION_HPP_
#define _SESSION_HPP_


class DB_con;
class Message_body;
class Message_reader;
class Message_writer;
class Message_processor;

#include <ctime>
#include <memory>
#include <deque>


class Session{
public:
  /*
  * @param sock, socket for communication
  */
  Session(int t_socket, std::shared_ptr<DB_con> t_db);

  /*
  * main function to call to process communication
  */
  void do_session();

  // int close();
  ~Session();
private:



  std::unique_ptr<Message_reader> m_reader;
  std::unique_ptr<Message_writer> m_writer;
  std::unique_ptr<Message_processor> m_processor;
  std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> m_to_send;
  int m_socket;
  std::shared_ptr<std::time_t> m_last_recv_time;
  std::shared_ptr<DB_con> m_db;


};
#endif
