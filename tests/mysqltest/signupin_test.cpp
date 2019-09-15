#include <mysql++.h>
#include <iostream>
#include <stdexcept>

// g++ signupin_test.cpp -std=c++17 -I /usr/local/include/mysql++/ -I /usr/include/mysql/ -lmysqlpp -lmysqlclient
//



class mydb
{
public:
  mydb()
  {
    this->conn = mysqlpp::Connection(false);

    if(!this->conn.connect("tl_test", "127.0.0.1:3306", "root", "root"))
    {
      std::cerr << "DB connection failed: " << this->conn.error() << std::endl;
      throw std::runtime_error("");
    }
  }

  /*
  *
  */
  void do_sign_up(std::string username, std::string password)
  {
    std::string SQL("INSERT into user (USERNAME, PASSWORD, DATA) VALUES ('"+ username +"', '"+password+"', '22')");
    // mysqlpp::Query query = conn.query(std::string("CREATE TABLE testtable (id INT PRIMARY KEY)"));

    mysqlpp::Query query = this->conn.query(SQL);
    bool boolres=query.exec();
    std::cout << boolres << " errnum " << query.errnum()<< query.error() <<" auto incre "<<  query.insert_id()<<std::endl;
    // errnum is 1062 for duplicates
  }

  /*
  *
  */
  void do_sign_in(std::string username, std::string password)
  {
    std::string SQL ("SELECT DATA from user where USERNAME = '"+ username +"' and PASSWORD = '" + password + "'");
    mysqlpp::Query query = this->conn.query(SQL);
    mysqlpp::StoreQueryResult res = query.store();
    if(res){
      std::cout<< "0 results"<<" error: "<< query.error()<<" error num: "<< query.errnum()<<std::endl;
    }
    std::cout<< "num result "<< res.num_rows()<<std::endl;
    mysqlpp::StoreQueryResult::const_iterator it;
    for (it = res.begin(); it != res.end(); ++it) {
        mysqlpp::Row row = *it;
        for(auto &i : row){
          int ex = i;
          ex += 11;
          std::cout << '\t' << ex << std::endl;
        }

    }
  }

private:
  mysqlpp::Connection conn;



};



int main(int argc, char** argv){
  if(argc != 3){
    std::cout << "wrong argc" << std::endl;
    return -1;
  }

  std::string username = argv[1];
  std::string password = argv[2];

  mydb db;

  db.do_sign_in(username, password);




}
