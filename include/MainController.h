#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MainController : public drogon::HttpController<MainController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MainController::DefaultRoute, "/");
    ADD_METHOD_TO(MainController::DefaultRoute, "/home");
    ADD_METHOD_TO(MainController::DefaultRoute, "/services");
    ADD_METHOD_TO(MainController::DefaultRoute, "/about");
    ADD_METHOD_TO(MainController::DefaultRoute, "/contact");
    ADD_METHOD_TO(MainController::NewContact, 
        "/contact/submit?fullname={}&email={}&message={}", Post
    );
    ADD_METHOD_TO(MainController::HealthCheck, "/health", Get);
    METHOD_LIST_END

    void DefaultRoute(const HttpRequestPtr& req, 
        std::function<void (const HttpResponsePtr &)> &&callback) const;

    void NewContact(const HttpRequestPtr& req, 
        std::function<void (const HttpResponsePtr &)> &&callback,
        std::string &&full_name,
        std::string &&email,
        std::string &&message) const;

    void HealthCheck(const HttpRequestPtr& req, 
        std::function<void (const HttpResponsePtr &)> &&callback) const;
};
