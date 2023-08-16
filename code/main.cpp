#include <iostream>
#include <mysql.h>
#include"Sql_print.h"
#include"sql_access.h"
using namespace std;
int main() {
    // 1. 初始化连接环境

    MYSQL *conn = mysql_init(nullptr);//初始化连接对象
    if (conn == nullptr) {
        printf("mysql_init() error\n");
        return -1;
    }
    // 2. 连接数据库服务器
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
    //printf("mysql api使用的默认编码: %s\n", mysql_character_set_name(conn));
    //mysql_set_character_set(conn, "utf4mb8");
    //printf("mysql api使用的默认编码: %s\n", mysql_character_set_name(conn));
    // 3. 执行一个sql语句
//    const char *query = "select * from read_test";//输入需要执行的语句
//    if (0 != mysql_query(conn, query)) {// 执行这个sql语句
//        printf("mysql_query() a失败了, 原因: %s\n", mysql_error(conn));
//        return -1;
//    }

    // 4. 取出结果集
//    MYSQL_RES *res = mysql_store_result(conn);
//    if (res == nullptr) {
//        printf("mysql_store_result() 失败了, 原因: %s\n", mysql_error(conn));
//        return -1;
//    }
    auto *ac =new sql_access(conn);
    ac->All_read();
    ac->print();
    ac->All_write();
    mysql_close(conn);
    return 0;
}

