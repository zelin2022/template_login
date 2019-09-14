/*
* Filename: db_core.cpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/



#include "db_core.hpp"

/*
*
*/
DB_core(const char* DB, const char* hostname, const char* username, const char* password)
{
  this->conn = std::make_unique<mysqlpp::Connection>(false);
}

/*
*
*/
~DB_core()
{

}

/*
*
*/
void execute(std::string query)
{


}

/*
*
*/
void execute(const char* query)
{

}
