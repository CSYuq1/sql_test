// Created by lenovo on 2023/8/4.
#include "sql_access.h"

vector<sql_access::sql_row> &sql_access::getSqlRows() {
    return rows;
}

int sql_access::All_read(MYSQL_RES *res) {
    // unsigned int num = mysql_num_fields(DEFAULT_RES);
    MYSQL_ROW row;
    rows.reserve(mysql_num_rows(res));
    while ((row = mysql_fetch_row(res)) != nullptr) {

        sql_row data_row(stoi(row[0]),
                         row[1],
                         row[2],
                         row[3],
                         row[4],
                         row[5],
                         row[6],
                         row[7],
                         row[8],
                         row[9]);
        rows.emplace_back(data_row);
    }
    return 0;
}

int sql_access::All_read() {
    MYSQL_RES *res;
    if ((res = mysql_store_result(conn)) == nullptr)
        return All_read(DEFAULT_RES);
    return All_read(res);

}

int sql_access::All_write(vector<sql_row> input_rows) {
   char *sql_insert_query;
    for (auto row: input_rows) {
        sprintf(sql_insert_query,"INSERT INTO write_test (id,device_id,device_desc,res_group,res_desc,dept,routing_id,operation_id,duration,sync_state) VALUES (%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s')",
                row.id,
                row.device_id.c_str(),
                row.device_desc.c_str(),
                row.res_group.c_str(),
                row.res_desc.c_str(),
                row.dept.c_str(),
                row.routing_id.c_str(),
                row.operation_id.c_str(),
                row.duration.c_str(),
                row.sync_state.c_str()
                );
        if (0 != mysql_query(conn, sql_insert_query)) {// 执行这个sql语句
               printf("mysql_query() a失败了, 原因: %s\n", mysql_error(conn));
             return -1;}
        }



    return 0;
}

int sql_access::All_write() {
    return All_write(this->getSqlRows());
}

void sql_access::print() {
    for (auto &row: rows) {
        row.print();
    }
}

void sql_access::sql_row::print() {
    printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", id,
           device_id.c_str(),
           device_desc.c_str(),
           res_group.c_str(),
           res_desc.c_str(),
           dept.c_str(),
           routing_id.c_str(),
           operation_id.c_str(),
           duration.c_str(),
           sync_state.c_str());
}

sql_access::sql_access(MYSQL *newconn) : conn(newconn) {
    mysql_query(this->conn, DEFAULT_READ_QUERY);
    this->DEFAULT_RES = mysql_store_result(conn);
}

sql_access::sql_row::sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc,
                             char *dept, char *routingId, char *operationId, char *duration, char *syncState) {
    this->id = id;
    this->device_id = deviceId;
    this->device_desc = deviceDesc;
    this->res_group = resGroup;
    this->res_desc = resDesc;
    this->dept = dept;
    this->routing_id = routingId;
    this->operation_id = operationId;
    this->duration = duration;
    this->sync_state = syncState;
}




