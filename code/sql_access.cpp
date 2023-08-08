// Created by lenovo on 2023/8/4.
#include <iostream>
#include "sql_access.h"

int sql_access::All_read(MYSQL_RES *res) {
    // unsigned int num = mysql_num_fields(DEFAULT_RES);
    MYSQL_ROW row;
    rows.reserve(mysql_num_rows(res));
    while ((row = mysql_fetch_row(res)) != nullptr) {
        rows.emplace_back(*row[0],
                          row[1],
                          row[2],
                          row[3],
                          row[4],
                          row[5],
                          row[6],
                          row[7],
                          row[8],
                          row[9]);
    }
    return 0;
}

int sql_access::ALL_read() {
    MYSQL_RES *res;

    if ((res = mysql_store_result(conn)) == nullptr)

        return 0;
}

vector<sql_access::sql_row> &sql_access::getSqlRows() {
    return rows;
}

void sql_access::print() {
    for (auto &row: rows) {
        row.print();
    }
}

sql_access::sql_access(MYSQL *newconn) : conn(newconn) {
    mysql_query(this->conn, DEFAULT_QUERY);
    this->DEFAULT_RES = mysql_store_result(conn);
}


sql_access::sql_row::sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc,
                             char *dept,
                             char *routingId, char *operationId, char *duration, char *syncState) {
    this->id = id;
    strcpy(this->device_id, deviceId);
    strcpy(this->device_desc, deviceDesc);
    strcpy(this->res_group, resGroup);
    strcpy(this->res_desc, resDesc);
    strcpy(this->dept, dept);
    strcpy(this->routing_id, routingId);
    strcpy(this->operation_id, operationId);
    strcpy(this->duration, duration);
    strcpy(this->sync_state, syncState);
}

void sql_access::sql_row::print() {
    printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", id,
           device_id,
           device_desc,
           res_group,
           res_desc,
           dept,
           routing_id,
           operation_id,
           duration,
           sync_state);
}

