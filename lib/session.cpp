/*
* Filename: session.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Session implementation
* Instruction:
*/
#include "session.hpp"


/*
* constructor
*/
Session::Session(int sock, std::shared_ptr<DB_core> db)
{
  if(sock < 0){
    throw std::runtime_error("Session created with bad socket value : " + std::to_string(sock));
  }
  this->mysock = sock;
  // this->is_closed = false;
  // this->incomplete_msg = std::make_shared<Message>(SESSION_STANDARD_MSG_LEN);
  this->last_recv_time = std::make_shared<std::time_t>();
  this-> reader = std::make_unique<Message_reader>(this->last_recv_time, this->mysock);
  this-> processor = std::make_unique<Message_processor>(db);
  this->db_core = db;
}

/*
*
*/
void Session::do_session()
{
  // // if this function is called, then there is data on fd's rx buffer
  // this->recv_all_msg();
  //
  // while(!this->complete_msgs.empty())
  // {
  //   this->process_one_msg();
  //   this->complete_msgs.pop();
  // }



  std::vector<std::shared_ptr<Message>> recvd_msg = this->reader.readall();
  this->processor.process_messages(recvd_msg);

}








// /*
// *
// */
// int Session::close()
// {
//   if(this->socket == -1){
//     return -1;
//   }
//   close(this->socket);
//   this->socket = -1;
//   return 0;
// }


// /*
// *
// */
// ssize_t Session::send(char* buffer, ssize_t len)
// {
//   ssize_t offset = 0;
//
//   while(len)
//   {
//     ssize_t sent = ::send(https://i.redd.it/glzojtm1ruj31.gifthis->socket, buffer + len, size, MSG_NOSIGNAL);
//
//     if(sent == -1)
//     {
//       if(errno == EINTR)
//       {
//         sent = 0;
//       }
//       else
//       {
//         perror("Session:send, ::send() return -1");
//         return -1;
//       }
//     }
//     // if(sent != size){
//     //   printf("Warning:: ::send() is truncating message       ");
//     // }
//     // printf("::send() has sent %d bytes \n", sent);
//
//     offset += sent;
//     len -= sent;
//   }
//   return offset;
// }



// /*
// *
// */
// bool Session::closed()
// {
//   return this->is_closed;
// }
