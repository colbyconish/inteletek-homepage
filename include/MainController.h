#pragma once

#include <aws/core/auth/AWSCredentialsProviderChain.h>

#include <drogon/HttpController.h>

using namespace drogon;

class MainController : public drogon::HttpController<MainController>
{
private:
    static constexpr char FROM_ADDRESS[] = "new-contact@inteletek.io";
    static constexpr char TO_ADDRESS[] = "colby.conish@inteletek.io";

public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MainController::DefaultRoute, "/", Get);
    ADD_METHOD_TO(MainController::DefaultRoute, "/home", Get);
    ADD_METHOD_TO(MainController::DefaultRoute, "/contact", Get);
    ADD_METHOD_TO(MainController::DefaultRoute, "/services", Get);
    ADD_METHOD_TO(MainController::DefaultRoute, "/about", Get);
    ADD_METHOD_TO(MainController::NewContact, 
        "/contact?fullname={}&email={}&message={}", Post);
    ADD_METHOD_TO(MainController::HealthCheck, "/health", Get);
    ADD_METHOD_TO(MainController::HealthCheck, "/health/", Get);
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

    static bool new_contact_inner(
        std::string &full_name, 
        std::string &email, 
        std::string &message);
};
