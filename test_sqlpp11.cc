/**
 * @file test_sqlpp11.cc
 * @author your name (you@domain.com)
 * @brief 测试sql11框架
 * @version 0.1
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/connection.h>

int main()
{
    sqlpp::sqlite3::connection_config config;

    config.path_to_database = "/tmp/mnc/mnc_sqlite3.db";

    sqlpp::sqlite3::connection connection(config);
}