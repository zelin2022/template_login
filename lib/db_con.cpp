/*
* Filename: db_con.cpp
* Author: Zelin Liu
* Date: 2019/09/12
* Description:
* Instruction:
*/





#include "db_con.hpp"

/*
*
*/
DB_con::DB_con(const char* DB, const char* hostname, const char* username, const char* password)
{
  this->m_conn = std::make_unique<mysqlpp::Connection>(false);
  this->m_conn->connect(DB, hostname, username, password);
}

/*
*
*/
DB_con::~DB_con()
{

}

/*
*
*/
void DB_con::exec(std::string SQL)
{
  mysqlpp::Query query = this->m_conn->query(SQL);
  if(!query.exec()){
    throw std::runtime_error("INSERT FAILED");
  }
}

/*
*
*/
template<class T>
std::vector<T> DB_con::store(std::string SQL)
{
  std::vector<T> output;
  mysqlpp::Query query = this->m_conn->query(SQL);
  mysqlpp::StoreQueryResult res = query.store();

  if(res.num_rows() == 0)
  {
    throw std::runtime_error("QUREY STORE RETURNS 0 ROW");
  }

  mysqlpp::StoreQueryResult::const_iterator iter;
  for(iter = res.begin(); iter!=res.end(); ++iter)
  {
    mysqlpp::Row row = *iter;
    for(auto &i : row)
    {
      output.push_back(i);
    }

  }

  return output;
}

/*
*
*/
std::string DB_con::get_last_error()
{
  return std::string(this->m_conn->error());
}
