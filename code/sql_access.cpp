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

        rows.emplace_back(stoi(row[0]),
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
        printf("Failed to prepare statement: Error: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return -1;
    }
    MYSQL_BIND bindParams[10];
    memset(bindParams, 0, sizeof(bindParams));
    bindParams[0].buffer_type = MYSQL_TYPE_LONG;
    bindParams[1].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[2].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[3].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[4].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[5].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[6].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[7].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[8].buffer_type = MYSQL_TYPE_VARCHAR;
    bindParams[9].buffer_type = MYSQL_TYPE_VARCHAR;
    for (auto row: input_rows) {
        unsigned int id = row.getId();
        bindParams[0].buffer = (void *) &id;
        bindParams[0].buffer_length = sizeof(row.getId());
        //char *device_id;//设备id
        bindParams[1].buffer = (void *) row.getDeviceId();
        bindParams[1].buffer_length = sizeof(row.getDeviceId());
        //char *device_desc;//设备描述
        bindParams[2].buffer = (void *) row.getDeviceDesc();
        bindParams[2].buffer_length = sizeof(row.getDeviceDesc());
        //char *res_group;//组
        bindParams[3].buffer = (void *) row.getResGroup();
        bindParams[3].buffer_length = sizeof(row.getResGroup());
        //char *res_desc;//组描述
        bindParams[4].buffer = (void *) row.getResDesc();
        bindParams[4].buffer_length = sizeof(row.getResDesc());
        //char *dept;//部门
        bindParams[5].buffer = (void *) row.getDept();
        bindParams[5].buffer_length = sizeof(row.getDept());
        //char *routing_id;//工艺id
        bindParams[6].buffer = (void *) row.getRoutingId();
        bindParams[6].buffer_length = sizeof(row.getRoutingId());
        // char *operation_id;//工序id
        bindParams[7].buffer = (void *) row.getOperationId();
        bindParams[7].buffer_length = sizeof(row.getOperationId());
        //char *duration;//时长
        bindParams[8].buffer = (void *) row.getDuration();
        bindParams[8].buffer_length = sizeof(row.getDuration());
        //char *sync_state;//同步状态
        bindParams[9].buffer = (void *) row.getSyncState();
        bindParams[9].buffer_length = sizeof(row.getSyncState());
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

unsigned int sql_access::sql_row::getId() const {
    return id;
}

const char *sql_access::sql_row::getDeviceId() const {
    return device_id;
}

const char *sql_access::sql_row::getDeviceDesc() const {
    return device_desc;
}

const char *sql_access::sql_row::getResGroup() const {
    return res_group;
}

const char *sql_access::sql_row::getResDesc() const {
    return res_desc;
}

const char *sql_access::sql_row::getDept() const {
    return dept;
}

const char *sql_access::sql_row::getRoutingId() const {
    return routing_id;
}

const char *sql_access::sql_row::getOperationId() const {
    return operation_id;
}

const char *sql_access::sql_row::getDuration() const {
    return duration;
}

const char *sql_access::sql_row::getSyncState() const {
    return sync_state;
}

const unsigned int sql_access::sql_row::getRowNum() const {
    return row_num;
}




