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
protected:
    class sql_row {
    public:
        unsigned int getId() const;

        const char *getDeviceId() const;

        const char *getDeviceDesc() const;

        const char *getResGroup() const;

        const char *getResDesc() const;

        const char *getDept() const;

        const char *getRoutingId() const;

        const char *getOperationId() const;

        const char *getDuration() const;

        const char *getSyncState() const;

    private:
        CONST unsigned int row_num=10 ;//记录字段的数量
    public:
        const unsigned int getRowNum() const;

    private:
        unsigned int id;//主键
        char device_id[256];//设备id
        char device_desc[256];//设备描述
        char res_group[256];//组
        char res_desc[256];//组描述
        char dept[256];//部门
        char routing_id[256];//工艺id
        char operation_id[256];//工序id
        char duration[256];//时长
        char sync_state[256];//同步状态
    public:
        sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc, char *dept,
                char *routingId, char *operationId, char *duration, char *syncState);

        void print();
    };
    MYSQL *conn;
    MYSQL_RES *DEFAULT_RES;
    vector<sql_row> rows;//将读取的row存入此处
public:
    CONST CHAR *DEFAULT_READ_QUERY = "SELECT * FROM read_test";
    CONST CHAR *DEFAULT_WRITE_PREPARE = "INSERT INTO write_test (id, device_id,device_desc,res_group,res_desc,dept,routing_id,operation_id,duration,sync_state) VALUES ( ? , ? , ? , ? , ? , ?, ? , ? , ? , ? )";//10个参数的预处理语句

    sql_access(MYSQL *newconn);

    vector<sql_row> &getSqlRows();

    void print();

    /*
     * 将result中所有的row读入到vector中
     */
    int All_read(MYSQL_RES *result);

    int All_read();

    int All_write(vector<sql_row> input_rows);
    int All_write();
};

#endif //SQL_TEST_SQL_READ_H
