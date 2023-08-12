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

int sql_access::All_read() {
    MYSQL_RES *res;
    if ((res = mysql_store_result(conn)) == nullptr)
        return All_read(DEFAULT_RES);
    return All_read(res);

}

int sql_access::All_write(vector<sql_row> input_rows) {
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (stmt == nullptr) {
        printf("Failed to initialize statement: Error: %s\n", mysql_stmt_error(stmt));
        return -1;
    }
    if (mysql_stmt_prepare(stmt, DEFAULT_WRITE_PREPARE, strlen(DEFAULT_WRITE_PREPARE)) != 0) {
        printf( "Failed to prepare statement: Error: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return -1;
        MYSQL_BIND bindParams[10];
        memset(bindParams, 0, sizeof(bindParams));

        unsigned int id;
        char param2[50];

        bindParams[0].buffer_type = MYSQL_TYPE_INT24;
        bindParams[0].buffer = (int  *)&id;

        bindParams[1].buffer_type = MYSQL_TYPE_VARCHAR;
        bindParams[1].buffer = (void *)param2;
        bindParams[1].buffer_length = sizeof(param2);

    }
    return 0;
}

void sql_access::print() {
    for (auto &row: rows) {
        row.print();
    }
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

sql_access::sql_access(MYSQL *newconn) : conn(newconn) {
    mysql_query(this->conn, DEFAULT_READ_QUERY);
    this->DEFAULT_RES = mysql_store_result(conn);
}



//void sql_access::close() {
//    mysql_free_result(res);
//    mysql_close(conn);
//
//}


sql_access::sql_row::sql_row(unsigned int id, char *deviceId, char *deviceDesc, char *resGroup, char *resDesc,
                             char *dept, char *routingId, char *operationId, char *duration, char *syncState) {
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




