cmake_minimum_required(VERSION 3.25)
project(sql_test)
set(CMAKE_CXX_STANDARD 23)
include_directories(C:\\Program\ Files\\MySQL\\MySQL\ Server\ 8.0\\include)
link_directories(C:\\Program\ Files\\MySQL\\MySQL\ Server\ 8.0\\lib)
link_libraries(libmysql)
add_executable(sql_test code/main.cpp
        code/Sql_print.cpp
        code/Sql_print.h
        code/Sql_read.cpp
        code/Sql_read.h)
target_link_libraries(sql_test libmysql.dll)

