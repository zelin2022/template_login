/*
* Filename: db_con.hpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/
#ifndef _DB_con_HPP_
#define _DB_con_HPP_

#include <mysql++.h>

class DB_con
{
public:
  DB_con(const char* DB, const char* hostname, const char* username, const char* password);
  ~DB_con();
  // void execute(std::string query);
  void exec(std::string SQL);
  template<class T>
  std::vector<T> store(std::string SQL);
  std::string get_last_error();

private:
  std::unique_ptr<mysqlpp::Connection> m_conn;
};
#endif
