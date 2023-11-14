/**
 * @file test_sqlite_orm.cc
 * @author your name (you@domain.com)
 * @brief 测试sqlite orm工具
 * @version 0.1
 * @date 2023-07-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <memory>
#include "sqlite_orm.h"

struct User 
{
    int id;
    std::string firstName;
    std::string lastName;
    int birthDate;
    std::unique_ptr<std::string> imageUrl;
    int typeId;
};

struct UserType 
{
    int id;
    std::string name;
};

int CreateDatabaseAndTable()
{
    auto storage = sqlite_orm::make_storage("db.sqlite", 
                                            sqlite_orm::make_table("users",
                                                                   sqlite_orm::make_column("id", &User::id, sqlite_orm::primary_key().autoincrement()),
                                                                   sqlite_orm::make_column("first_name", &User::firstName),
                                                                   sqlite_orm::make_column("last_name", &User::lastName),
                                                                   sqlite_orm::make_column("birth_data", &User::birthDate),
                                                                   sqlite_orm::make_column("image_url", &User::imageUrl),
                                                                   sqlite_orm::make_column("type_id", &User::typeId)
                                                                   )
                                            );
    storage.sync_schema();

    auto current_timestamp = storage.current_timestamp();
    std::cerr << "current timestamp = " << current_timestamp << std::endl;

    User u 
    {
        1,
        "aaa",
        "bbb",
        2023,
        std::make_unique<std::string>("/home/user/a.jpeg"),
        23
    };
    storage.insert(u);

    return 0;
}

int main()
{
    CreateDatabaseAndTable();
}