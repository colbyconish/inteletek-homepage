#pragma once

#include "Database.hpp"
#include <drogon/HttpController.h>

using namespace drogon;

class MainController : public drogon::HttpController<MainController>
{
private:
    LocalDatabaseConnection _db_conn;

public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MainController::DefaultRoute, "/", "InsecureFilter");
    ADD_METHOD_TO(MainController::DefaultRoute, "/home", "InsecureFilter");
    ADD_METHOD_TO(MainController::ProductsRoute, "/products", "InsecureFilter");
    ADD_METHOD_TO(MainController::AboutRoute, "/about", "InsecureFilter");
    ADD_METHOD_TO(MainController::ContactRoute, "/contact", "InsecureFilter");
    ADD_METHOD_TO(MainController::NewContact, "/contact/submit?fullname={}&email={}&message={}", Post, "InsecureFilter");
    METHOD_LIST_END

    void DefaultRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void ProductsRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void AboutRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void ContactRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void NewContact(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback,
        std::string &&full_name,
        std::string &&email,
        std::string &&message) const;
};
