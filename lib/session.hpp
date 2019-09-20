/*
* Filename: session.hpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: TLS_Session definition
* Instruction:
*/
#ifndef _SESSION_HPP_
#define _SESSION_HPP_
#include <cstring>

#include "db_con.hpp"
#include "message_reader.hpp"
#include "message_writer.hpp"
#include "message_body.hpp"
#include "message_processor.hpp"


class Session{
public:
  /*
  * @param sock, socket for communication
  */
  Session(int sock, std::shared_ptr<DB_con> db);

  /*
  * main function to call to process communication
  */
  void do_session();

  // int close();
  ~Session();
private:



  std::unique_ptr<Message_reader> reader;
  std::unique_ptr<Message_writer> writer;
  std::unique_ptr<Message_processor> processor;
  std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> to_send;
  int mysock;
  std::shared_ptr<std::time_t> last_recv_time;
  std::shared_ptr<DB_con> db_con;


};
#endif
