#include "Database.hpp"

LocalDatabaseConnection::LocalDatabaseConnection()
{
    mongocxx::uri uri("mongodb://localhost:27017");
    _client = mongocxx::client(uri);
}

