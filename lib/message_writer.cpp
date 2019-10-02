/*
* Filename: message_writer.cpp
* Author: Zelin Liu
* Date: 2019/09/15
* Description:
* Instruction:
*/
#include "message_writer.hpp"
#include "message_body.hpp"
/*
*
*/
Message_writer::Message_writer(int t_socket)
:m_socket(t_socket)
{

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
void Message_writer::write_all(std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> t_in_queue)
{
  while(!t_in_queue->empty())
  {
    ssize_t ret = this->write_message(t_in_queue->front());
    if( ret != t_in_queue->front()->m_data_len)
    {
      throw std::runtime_error("writing failed: expected len:" + std::to_string(t_in_queue->front()->m_data_len)+" actual len:"+std::to_string(ret)+"\n");
    }
    t_in_queue->pop_front();
  }


}

/*
*
*/
ssize_t Message_writer::write(char* t_buffer, size_t t_len)
{
  int len_buf = t_len;
  return this->sendall(t_buffer, &len_buf);
}



/*
*
*/
ssize_t Message_writer::write_message(std::shared_ptr<Message_body> t_message)
{
  int len_buf = t_message->m_data_len;
  return this->sendall(t_message->m_data, &len_buf);
}

/*
*
*/
ssize_t Message_writer::sendall(char *t_buf, int *t_len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *t_len; // how many we have left to send
    int n;

    while(total < *t_len) {
        n = send(this->m_socket, t_buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *t_len = total; // return number actually sent here

    return n==-1?n:total; // return -1 on failure, 0 on success
}
