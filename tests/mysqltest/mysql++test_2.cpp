// #include <mysql++.h>

#include "../../lib/db_con.hpp"
// #include <iomanip>

using namespace std;

int
main(int argc, char *argv[])
{
  std::shared_ptr<DB_con> test = std::make_shared<DB_con>("tl_test", "127.0.0.1:3306", "root", "root");
}
