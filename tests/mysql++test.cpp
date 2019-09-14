// compile with
// g++ mysql++test.cpp -std=c++17 -I /usr/local/include/mysql++/ -I /usr/include/mysql/ -lmysqlpp -lmysqlclient
//
// #include <mysql++.h>
// #include <stdlib.h>
//
// using namespace std;
// using namespace mysqlpp;
//
// int main() {
//     // try {
//         Connection conn(false);
//         conn.connect("tl_test", "tcp://127.0.0.1:3306", "root", "root");
//         Query query = conn.query();
//         query << "CREATE TABLE testtable (id INT PRIMARY KEY);";
//         query.execute();
//     // } catch (BadQuery er) { // handle any connection or
//     //     // query errors that may come up
//     //     cerr << "Error: " << er.what() << endl;
//     //     return -1;
//     // } catch (const BadConversion& er) {
//     //     // Handle bad conversions
//     //     cerr << "Conversion error: " << er.what() << endl <<
//     //             "\tretrieved data size: " << er.retrieved <<
//     //             ", actual size: " << er.actual_size << endl;
//     //     return -1;
//     // } catch (const Exception& er) {
//     //     // Catch-all for any other MySQL++ exceptions
//     //     cerr << "Error: " << er.what() << endl;
//     //     return -1;
//     // }
//
//     return (EXIT_SUCCESS);
// }

// #include "cmdline.h"
// #include "printdata.h"

#include <mysql++.h>

#include <iostream>
#include <iomanip>

using namespace std;

int
main(int argc, char *argv[])
{
    // Get database access parameters from command line
    // mysqlpp::examples::CommandLine cmdline(argc, argv);
    // if (!cmdline) {
    //     return 1;
    // }

    // Connect to the sample database.
    mysqlpp::Connection conn(false);
    if (conn.connect("tl_test", "127.0.0.1:3306", "root", "root")) {
        // Retrieve a subset of the sample stock table set up by resetdb
        // and display it.
        mysqlpp::Query query = conn.query(string("CREATE TABLE testtable (id INT PRIMARY KEY)"));
        if (mysqlpp::StoreQueryResult res = query.store()) {
            cout << "We have:" << endl;
            mysqlpp::StoreQueryResult::const_iterator it;
            for (it = res.begin(); it != res.end(); ++it) {
                mysqlpp::Row row = *it;
                cout << '\t' << row[0] << endl;
            }
        }
        else {
            cerr << "Failed to get item list: " << query.error() << endl;
            return 1;
        }

        return 0;
    }
    else {
        cerr << "DB connection failed: " << conn.error() << endl;
        return 1;
    }
}
