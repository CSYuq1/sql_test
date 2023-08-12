//
// Created by lenovo on 2023/8/4.
//
#include "mysql.h"
#include <vector>
#include <cstring>
#include <iostream>

#ifndef SQL_TEST_SQL_READ_H
#define SQL_TEST_SQL_READ_H
using namespace std;

/*
 * 传入一个mysql连接以初始化此类
 */
class sql_access {
    class sql_row {
        unsigned int id;//主键
        string device_id;//设备id
        string  device_desc;//设备描述
        string res_group;//组
        string res_desc;//组描述
        string dept;//部门
        string routing_id;//工艺id
        string operation_id;//工序id
        string duration;//时长
        string sync_state;//同步状态
    public:
        sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc, char *dept,
                char *routingId, char *operationId, char *duration, char *syncState);

        void print();
    };

    MYSQL *conn;
    MYSQL_RES *DEFAULT_RES;
    vector<sql_row> rows;//将读取的row存入此处
public:
    CONST CHAR *DEFAULT_READ_QUERY = "select * from read_test";
    CONST CHAR *DEFAULT_WRITE_PREPARE = "INSERT INTO write_test (id, "
                                        "device_id,"
                                        "device_desc,"
                                        "res_group,"
                                        "res_desc,"
                                        "dept,"
                                        "routingId,"
                                        "operationId,"
                                        "duration,"
                                        "syncState) "
                                        "VALUES ( ? , ? , ? , ? , ? , ?, ? , ? , ? , ? )";//10个参数的预处理语句

    sql_access(MYSQL *newconn);

    vector<sql_row> &getSqlRows();

    void print();

    /*
     * 将result中所有的row读入到vector中
     */
    int All_read(MYSQL_RES *result);

    int All_read();

    int All_write(vector<sql_row> input_rows);
};

#endif //SQL_TEST_SQL_READ_H
