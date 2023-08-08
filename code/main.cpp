#include <iostream>
#include <mysql.h>
#include"Sql_print.h"
#include"sql_access.h"
using namespace std;

/*
 * aaaaaaaaaaa
 */
int main() {
    // 1. 初始化连接环境
    MYSQL *mysql = mysql_init(nullptr);//初始化连接对象
    if (mysql == nullptr) {
        printf("mysql_init() error\n");
        return -1;
    }
    // 2. 连接数据库服务器
    mysql = mysql_real_connect(mysql, "localhost",
                               "root",
                               "yanyuqisql",
                               "test",
                               3306,
                               nullptr,
                               0);
    if (mysql == nullptr) {
        printf("mysql_real_connect() error\n");
        return -1;
    }

    // 3. 执行一个sql语句
    const char *query = "select * from read_test";//输入需要执行的语句
    if (0 != mysql_query(mysql, query)) {// 执行这个sql语句
        printf("mysql_query() a失败了, 原因: %s\n", mysql_error(mysql));
        return -1;
    }

    // 4. 取出结果集
    MYSQL_RES *res = mysql_store_result(mysql);
    if (res == nullptr) {
        printf("mysql_store_result() 失败了, 原因: %s\n", mysql_error(mysql));
        return -1;
    }
    auto *rd =new sql_access;
    rd->All_read(res);
    rd->print();
    // 5. 得到结果集中的列数
 //   Sql_print::print_all_field(res);
 //   Sql_print::print_all_rows(res);

    //  释放资源 - 结果集
    mysql_free_result(res);
    mysql_close(mysql);
    return 0;
}

