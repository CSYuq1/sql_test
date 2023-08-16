#include <iostream>
#include <mysql.h>
#include"Sql_print.h"
#include"sql_access.h"
using namespace std;
int main() {
    // 1. ��ʼ�����ӻ���

    MYSQL *conn = mysql_init(nullptr);//��ʼ�����Ӷ���
    if (conn == nullptr) {
        printf("mysql_init() error\n");
        return -1;
    }
    // 2. �������ݿ������
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
    //printf("mysql apiʹ�õ�Ĭ�ϱ���: %s\n", mysql_character_set_name(conn));
    //mysql_set_character_set(conn, "utf4mb8");
    //printf("mysql apiʹ�õ�Ĭ�ϱ���: %s\n", mysql_character_set_name(conn));
    // 3. ִ��һ��sql���
//    const char *query = "select * from read_test";//������Ҫִ�е����
//    if (0 != mysql_query(conn, query)) {// ִ�����sql���
//        printf("mysql_query() aʧ����, ԭ��: %s\n", mysql_error(conn));
//        return -1;
//    }

    // 4. ȡ�������
//    MYSQL_RES *res = mysql_store_result(conn);
//    if (res == nullptr) {
//        printf("mysql_store_result() ʧ����, ԭ��: %s\n", mysql_error(conn));
//        return -1;
//    }
    auto *ac =new sql_access(conn);
    ac->All_read();
    ac->print();
    ac->All_write();
    mysql_close(conn);
    return 0;
}

