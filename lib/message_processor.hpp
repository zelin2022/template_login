/*
* Filename: message_processor.hpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/
#ifndef _MESSAGE_PROCESSOR_HPP_
#define _MESSAGE_PROCESSOR_HPP_

#include "message_body.hpp"
#include "db_con.hpp"
#include "message_builder.hpp"
#include "utility.hpp"
#include "macro.h"
#include <vector>
#include <memory>
#include <deque>


class Message_processor
{
public:
  Message_processor(std::shared_ptr<DB_con> dbcon, std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> queue);
  ~Message_processor();
  void process_messages(std::vector<std::shared_ptr<Message_body>> input);

private:
  void process_one_msg(std::shared_ptr<Message_body> msg);

  std::shared_ptr<std::deque<std::shared_ptr<Message_body>>> send_queue;
  std::shared_ptr<DB_con> db;
  void do_sign_up(std::shared_ptr<Message_body> msg);
  void do_sign_in(std::shared_ptr<Message_body> msg);


};
#endif
