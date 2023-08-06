#include <mysql.h>
#include<vector>

#ifndef SQL_TEST_SQL_PRINT2_H
#define SQL_TEST_SQL_PRINT2_H

class Sql_print {
public:
/*
  作用打印所有的字段名称
  */
    static int print_all_field(MYSQL_RES *res);

/*
 作用:输出所有行的内容
 */
    static int print_all_rows(MYSQL_RES *res);
};

#endif
















/*
    6. 得到所有列的名字, 并且输出
    unsigned int num = mysql_num_fields(res);
   fields = mysql_fetch_fields(res);
   for (int i = 0; i < num; ++i)
   printf("%s\t\t", fields[i].name);
   printf("\n");


 7. 遍历结果集中所有的行
    while ((row = mysql_fetch_row(res)) != NULL) {
    将当前行中的每一列信息读出
    for (int i = 0; i < num; ++i) {
    printf("%s\t\t", row[i]);
      }
    printf("\n");
   }

 9. 写数据库
 以下三条是一个完整的操作, 对应的是一个事务
 设置事务为手动提交
    mysql_autocommit(mysql, 0);
   int ret1 = mysql_query(mysql, "insert into dept values(61, '海军', '圣地玛丽乔亚')");
   int ret2 = mysql_query(mysql, "insert into dept values(62, '七武海', '世界各地')");
   int ret3 = mysql_query(mysql, "insert into dept values(63, '四皇', '新世界')");
   printf("ret1 = %d, ret2 = %d, ret3 = %d\n", ret1, ret2, ret3);

    if (ret1 == 0 && ret2 == 0 && ret3 == 0) {
 提交事务
       mysql_commit(mysql);
    } else {
        mysql_rollback(mysql);
    }

释放数据库资源
*/