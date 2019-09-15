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



class Session{
public:
  /*
  * @param sock, socket for communication
  */
  Session(int sock, std::shared_ptr<DB_core> db);

  /*
  * main function to call to process communication
  */
  void do_session();

  // int close();
  ~Session();
private:



  std::unique_ptr<Message_reader> reader;
  std::unique_ptr<Message_processor> processor;
  std::shared_ptr<std::deque<std::shared_ptr<Message>>> to_send;
  int mysock;
  std::shared_ptr<std::time_t> last_recv_time
  std::shared_ptr<DB_core> db_core;


};
#endif
