/**
 * @file test_sqlite3.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "sqlite3.h"
#include <iostream>
#include <string>

static const char *sql_file = "/home/user/zjy-190/workspace/unit_test/data/sql/sqlite3.db";

int main()
{
    int res;
    sqlite3 *db;
    
    res = sqlite3_open(sql_file, &db);
    if (res != SQLITE_OK)
    {
        return -1;
    }

    const char *select_tables_sql = "create table test (key INT, value TEXT)";
    res = sqlite3_exec(db, select_tables_sql, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK)
    {
        std::cerr << "failed to execute sql command: " << select_tables_sql << std::endl;
        sqlite3_close(db);
        return -1;
    }
    std::cerr << "success" << std::endl;
    sqlite3_close(db);
    
    return 0;
}