/*
* Filename: message_writer.cpp
* Author: Zelin Liu
* Date: 2019/09/15
* Description:
* Instruction:
*/
#include "message_writer.hpp"

/*
*
*/
Message_writer::Message_writer(int sock)
{
    this->socket = sock;
}

/*
*
*/
Message_writer::~Message_writer()
{

}

/*
*
*/
void Message_writer::write_all(std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> in)
{
  while(!in->empty())
  {
    ssize_t ret = this->write_message(in->front());
    if( ret != in->front()->data_len)
    {
      throw std::runtime_error("writing failed: expected len:" + std::to_string(in->front()->data_len)+" actual len:"+std::to_string(ret)+"\n");
    }
    in->pop_front();
  }


}

/*
*
*/
ssize_t Message_writer::write(char* buffer, size_t len)
{
  int len_buf = len;
  return this->sendall(buffer, &len_buf);
}



/*
*
*/
ssize_t Message_writer::write_message(std::shared_ptr<Message_body> message)
{
  int len_buf = message->data_len;
  return this->sendall(message->data, &len_buf);
}

/*
*
*/
ssize_t Message_writer::sendall(char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    while(total < *len) {
        n = send(this->socket, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?n:total; // return -1 on failure, 0 on success
}
