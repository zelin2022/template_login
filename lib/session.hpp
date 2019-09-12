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
  Session(int sock);

  /*
  * main function to call to process communication
  */
  void do_session();

  // int close();
  ~Session();
private:



  std::unique_ptr<Message_reader> reader;

  int mysock;
  std::shared_ptr<std::time_t> last_recv_time


};
#endif
