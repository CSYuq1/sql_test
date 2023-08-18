#include <iostream>
#include <mysql.h>
#include"Sql_print.h"
#include"sql_access.h"

using namespace std;

int main() {
    MYSQL *conn = mysql_init(nullptr);//????????????
    if (conn == nullptr) {
        printf("mysql_init() error\n");
        return -1;
    }
    conn = mysql_real_connect(conn, "localhost",
                              "root",
                              "yanyuqisql",
                              "test",
                              3306,
                              nullptr,
                              0);
    if (conn == nullptr) {
        printf("mysql_real_connect() error\n");
        return -1;
    }
    auto *ac = new sql_access(conn);
    ac->All_read();
    ac->print();
    ac->All_write();
    mysql_close(conn);
    return 0;
}

