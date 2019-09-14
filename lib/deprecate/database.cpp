/*
* Filename: database.cpp
* Author: Zelin Liu
* Date: 2019/08/28
* Description: Database definition
* Instruction:
*/


/*
*
*/
Database::Database()
{
  /* Create a connection */
  this->driver = get_driver_instance();
  this->con = this->driver->connect(DATABASE_CONNECT_ADDR, DATABASE_CONNECT_USERNAME, DATABASE_CONNECT_PASSWORD);
  /* Connect to the MySQL test database */
  this->con->setSchema(DATABASE_TARGET_DATABASE);

  this->stmt = this->con->createStatement();
  // this->res = this->stmt->executeQuery("INSERT 'tom' name");

}

/*
*
*/
~Database::Database()
{
  delete(this->driver);
  delete(this->con);
  delete(this->stmt);
  delete(this->res);
}

/*
*
*/
void Database::signup(Message msg)
{

}

/*
*
*/
void Database::signin(Message msg, std::string& userdata)
{

}

/*
*
*/
std::string Database::array_to_string(char* data, int len)
{
  std::string s;
  for(int i = 0; i < len; i++)
  {
    s = s + data[i];
  }
  return s;
}
