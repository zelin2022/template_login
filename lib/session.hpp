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

  int close();
  ~Session();
private:
  void recv_msg();
  void process_one_msg();
  ssize_t send(char* buffer, ssize_t len);
  ssize_t receive(char* buffer, ssize_t* len);

  std::queue<std::shared__ptr<Message>> complete_msgs;
  std::shared_ptr<Message> incomplete_msg;

  int mysock;
  std::time_t last_recv_time;
  bool is_closed;
};
#endif
