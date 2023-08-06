//
// Created by lenovo on 2023/8/4.
//
#include "mysql.h"
#include <vector>
#include <string>

#ifndef SQL_TEST_SQL_READ_H
#define SQL_TEST_SQL_READ_H
using namespace std;

class Sql_read {

    class sql_row {
        unsigned int id;//主键
        char device_id[51];//设备id
        char device_desc[256];//设备描述
        char res_group[256];//组
        char res_desc[256];//组描述
        char dept[256];//部门
        char routing_id[201];//工艺id
        char operation_id[201];//工序id
        char duration[10];//时长
        char sync_state[10];//同步状态
    public:
        sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc, char *dept,
                char *routingId, char *operationId, char *duration, char *syncState);

        void print();
    };

    vector<sql_row> rows;//将读取的row存入此处
public:
    vector<sql_row> &getSqlRows();

    void print();

    /*
     * 将result中所有的row读入到vector中
     */
    int All_read(MYSQL_RES *result);
};

#endif //SQL_TEST_SQL_READ_H
