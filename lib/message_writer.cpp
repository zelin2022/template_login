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
ssize_t write(char* buffer, size_t len)
{
  int len_buf = len;
  return this->sendall(buffer, &len_buf)? len:-1;
}

/*
*
*/
void write_message(std::shared_ptr<Message_body> message)
{
  int len_buff = message->data_len;
  return this->sendall(message->data, &len_buf)? message->data_len:-1;
}

/*
*
*/
bool sendall(char *buf, int *len)
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

    return n==-1?false:true; // return -1 on failure, 0 on success
}
