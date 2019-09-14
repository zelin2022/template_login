/*
* Filename: database.hpp
* Author: Zelin Liu
* Date: 2019/08/28
* Description: Database definition
* Instruction:
*/

#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class Database
{
public:
  Database();
  ~Database();
  void signup();
  void signin();
  static std::string array_to_string(char* data, int len);
private:
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

};
#endif
