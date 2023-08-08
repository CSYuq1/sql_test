#include <iostream>
#include <mysql.h>
#include"Sql_print.h"
#include"sql_access.h"
using namespace std;

/*
 * aaaaaaaaaaa
 */
int main() {
    // 1. ��ʼ�����ӻ���
    MYSQL *mysql = mysql_init(nullptr);//��ʼ�����Ӷ���
    if (mysql == nullptr) {
        printf("mysql_init() error\n");
        return -1;
    }
    // 2. �������ݿ������
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

    // 3. ִ��һ��sql���
    const char *query = "select * from read_test";//������Ҫִ�е����
    if (0 != mysql_query(mysql, query)) {// ִ�����sql���
        printf("mysql_query() aʧ����, ԭ��: %s\n", mysql_error(mysql));
        return -1;
    }

    // 4. ȡ�������
    MYSQL_RES *res = mysql_store_result(mysql);
    if (res == nullptr) {
        printf("mysql_store_result() ʧ����, ԭ��: %s\n", mysql_error(mysql));
        return -1;
    }
    auto *rd =new sql_access;
    rd->All_read(res);
    rd->print();
    // 5. �õ�������е�����
 //   Sql_print::print_all_field(res);
 //   Sql_print::print_all_rows(res);

    //  �ͷ���Դ - �����
    mysql_free_result(res);
    mysql_close(mysql);
    return 0;
}

