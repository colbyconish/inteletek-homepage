#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

enum class Pages 
{
    Home,
    Products,
    About,
    Contact
};
inline const char *to_string(Pages page)
{
    static const char *names[] =
    {
        "Home",
        "Products",
        "About",
        "Contact"
    };

    return names[(int) page];
}

class MainController : public drogon::HttpController<MainController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MainController::DefaultRoute, "/", "InsecureFilter");
    ADD_METHOD_TO(MainController::DefaultRoute, "/home", "InsecureFilter");
    ADD_METHOD_TO(MainController::ProductsRoute, "/products", "InsecureFilter");
    ADD_METHOD_TO(MainController::AboutRoute, "/about", "InsecureFilter");
    ADD_METHOD_TO(MainController::ContactRoute, "/contact", "InsecureFilter");
    METHOD_LIST_END

    void DefaultRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void ProductsRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void AboutRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void ContactRoute(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
};
