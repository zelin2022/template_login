/*
* Filename: session.h
* Author: Zelin Liu
* Date: 2019/08/13
* Description: TLS_Session definition
* Instruction:
*/
#ifndef _SESSION_H_
#define _SESSION_H_
class Session{
public:
  Session(int sock);
  ssize_t send(char* buffer, ssize_t len);
  ssize_t receive(char* buffer, ssize_t* len);
  int close();
  ~Session();
private:
  int mysock;
  std::time_t last_recv_time;
};
#endif
