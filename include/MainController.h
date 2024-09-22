#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MainController : public drogon::HttpController<MainController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MainController::DefaultRoute, "/", "InsecureFilter");
    ADD_METHOD_TO(MainController::DefaultRoute, "/home", "InsecureFilter");
    METHOD_LIST_END
    void DefaultRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
};
