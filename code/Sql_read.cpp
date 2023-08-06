// Created by lenovo on 2023/8/4.
#include <iostream>
#include "Sql_read.h"

int Sql_read::All_read(MYSQL_RES *res) {
    // unsigned int num = mysql_num_fields(res);
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

vector<Sql_read::sql_row> &Sql_read::getSqlRows() {
    return rows;
}

void Sql_read::print() {
    for (auto &row: rows) {
        row.print();
    }
}

Sql_read::sql_row::sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc, char *dept,
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

void Sql_read::sql_row::print() {
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


