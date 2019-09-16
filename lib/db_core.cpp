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
DB_core::DB_core(const char* DB, const char* hostname, const char* username, const char* password)
{
  this->conn = std::make_unique<mysqlpp::Connection>(false);
}

/*
*
*/
~DB_core::DB_core()
{

}

/*
*
*/
void DB_core::exec(std::string SQL)
{
  mysqlpp::Query query = this->conn.query(SQL);
  if(!query.exec()){
    throw std::runtime_error("INSERT FAILED");
  }
}

/*
*
*/
  template<class T> std::vector<T> DB_core::store(std::string SQL, T type_example)
{
  std::vector<t> output;
  mysqlpp::Query query = this->conn.query(SQL);
  mysqlpp::StoreQueryResult res = query.store();

  if(res.num_rows() == 0)
  {
    throw std::runtime_error("QUREY STORE RETURNS 0 ROW");
  }

  mysqlpp::StoreQueryResult::const_iterator iter;
  for(iter = res.begin(); iter!=res.end; ++iter)
  {
    mysqlpp::Row row = *it;
    for(auto &i : row)
    {
      output.push_back(i);
    }

  }


}

/*
*
*/
std::string get_last_error()
{
  return std::string(this->conn.error());
}
