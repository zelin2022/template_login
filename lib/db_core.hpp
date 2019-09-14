/*
* Filename: db_core.hpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/
#ifndef _DB_CORE_HPP_
#define _DB_CORE_HPP_
class DB_core
{
public:
  DB_core(const char* DB, const char* hostname, const char* username, const char* password);
  ~DB_core();
  void execute(std::string query);
  void execute(const char* query);
private:
  std::unique_ptr<mysqlpp::Connection> conn;
};
#endif
