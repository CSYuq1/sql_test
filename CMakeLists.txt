cmake_minimum_required(VERSION 3.25)
project(sql_test)
set(CMAKE_CXX_STANDARD 23)
include_directories(C:\\Users\\yanyu\\CLionProjects\\sql_test\\include)
link_directories(C:\\Users\\yanyu\\CLionProjects\\sql_test\\lib)
link_libraries(libmysql)
add_executable(sql_test code/main.cpp
        code/Sql_print.cpp
        code/Sql_print.h
        code/sql_access.cpp
        code/sql_access.h)
target_link_libraries(sql_test libmysql.dll)

