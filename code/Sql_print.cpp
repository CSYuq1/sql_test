//
// Created by lenovo on 2023/8/4.
//

#include <cstdio>
#include "Sql_print.h"

int Sql_print::print_all_field(MYSQL_RES *res) {
    unsigned int num = mysql_num_fields(res);
    //  得到所有列的名字, 并且输出
    MYSQL_FIELD *fields = mysql_fetch_fields(res);
    for (int i = 0; i < num; ++i)
        printf("%s\t\t", fields[i].name);
    return 0;
}


int Sql_print::print_all_rows(MYSQL_RES *res) {
    unsigned int num = mysql_num_fields(res);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr) {

        for (int i = 0; i < num; ++i) {
            printf("%s\t", row[i]);
        }
        printf("\n");
    }
    return 0;
}





