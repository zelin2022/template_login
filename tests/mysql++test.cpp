// compile with
// g++ mysql++test.cpp -std=c++17 -I /usr/local/include/mysql++/ -I /usr/include/mysql/ -lmysqlpp -lmysqlclient

#include <mysql++.h>
#include <stdlib.h>

using namespace std;
using namespace mysqlpp;

int main() {
    try {
        Connection conn(false);
        conn.connect("DB NAME", "DB HOST probably localhost", "DB USER", "DB PASS");
        Query query = conn.query();
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}
