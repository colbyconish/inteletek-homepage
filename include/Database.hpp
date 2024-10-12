#pragma once

#include <string>

#include <drogon/HttpController.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <iostream>

struct ContactQuery
{
    std::string full_name;
    std::string email;
    std::string message;
};

namespace drogon
{
template <>
inline ContactQuery fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    ContactQuery query; 
    if(json)
    {
        query.full_name = (*json)["fullname"].asString();
        query.message = (*json)["message"].asString();
        query.email = (*json)["email"].asString();
    }
    else
    {
        std::cout << "Failed to read contact object." << std::endl;
    }
    return query;
}
}

class LocalDatabaseConnection
{
private:
    static mongocxx::instance _instance;
    mongocxx::client _client;

public:
    LocalDatabaseConnection();
};

