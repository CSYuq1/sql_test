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
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (stmt == nullptr) {
        printf("Failed to initialize statement: Error: %s\n", mysql_stmt_error(stmt));
        return -1;
    }
    if (mysql_stmt_prepare(stmt, DEFAULT_WRITE_PREPARE, strlen(DEFAULT_WRITE_PREPARE)) != 0) {
        printf("Failed to prepare statement: Error: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return -1;
    }
    MYSQL_BIND bindParams[10];
    memset(bindParams, 0, sizeof(bindParams));
    bindParams[0].buffer_type = MYSQL_TYPE_LONG;
    for (int i = 1; i < 10; i++)
        bindParams[i].buffer_type = MYSQL_TYPE_STRING;
    for (auto row: input_rows) {
        unsigned int id = row.id;
        bindParams[0].buffer = (void *) &id;
        bindParams[0].buffer_length = sizeof(row.id);
        //char *device_id;//设备id
        bindParams[1].buffer = (void *) row.device_id.c_str();
        bindParams[1].buffer_length = sizeof(row.device_id);
        //char *device_desc;//设备描述
        bindParams[2].buffer = (void *) row.device_desc.c_str();
        bindParams[2].buffer_length = sizeof(row.device_desc);
        //char *res_group;//组
        bindParams[3].buffer = (void *) row.res_group.c_str();
        bindParams[3].buffer_length = sizeof(row.res_group);
        //char *res_desc;//组描述
        bindParams[4].buffer = (void *) row.res_desc.c_str();
        bindParams[4].buffer_length = sizeof(row.res_desc);
        //char *dept;//部门
        bindParams[5].buffer = (void *) row.dept.c_str();
        bindParams[5].buffer_length = sizeof(row.dept);
        //char *routing_id;//工艺id
        bindParams[6].buffer = (void *) row.routing_id.c_str();
        bindParams[6].buffer_length = sizeof(row.routing_id);
        // char *operation_id;//工序id
        bindParams[7].buffer = (void *) row.operation_id.c_str();
        bindParams[7].buffer_length = sizeof(row.operation_id);
        //char *duration;//时长
        bindParams[8].buffer = (void *) row.duration.c_str();
        bindParams[8].buffer_length = sizeof(row.duration);
        //char *sync_state;//同步状态
        bindParams[9].buffer = (void *) row.sync_state.c_str();
        bindParams[9].buffer_length = sizeof(row.sync_state);
        if (mysql_stmt_bind_param(stmt, bindParams) != 0) {
            printf("Failed to bind parameters in row : Error: %s\n", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt);
            mysql_close(conn);
            return 1;
        }

        if (mysql_stmt_execute(stmt) != 0) {
            printf("Failed to execute statement in row : Error: %s\n", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt);
            mysql_close(conn);
            return 1;
        }

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

int sql_access::All_write() {
    return All_write(this->getSqlRows());
}



//void sql_access::close() {
//    mysql_free_result(res);
//    mysql_close(conn);
//
//}


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




