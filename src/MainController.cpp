#include "MainController.h"
#include "Pages.hpp"

void MainController::DefaultRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    data.insert("page", Pages::Home);
    auto resp=HttpResponse::newHttpViewResponse("home.csp", data);
    callback(resp);
}

void MainController::ProductsRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    data.insert("page", Pages::Products);
    auto resp=HttpResponse::newHttpViewResponse("comingsoon.csp", data);
    callback(resp);
}

void MainController::AboutRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    data.insert("page", Pages::About);
    auto resp=HttpResponse::newHttpViewResponse("comingsoon.csp", data);
    callback(resp);
}

void MainController::NewContact(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback,
        std::string &&full_name,
        std::string &&email,
        std::string &&message) const
{	
    std::cout << "New Contact: " 
        << std::endl << full_name 
        << std::endl << email 
        << std::endl << message 
        << std::endl;

    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);
}

void MainController::ContactRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    data.insert("page", Pages::Contact);
    auto resp=HttpResponse::newHttpViewResponse("contact.csp", data);
    callback(resp);
}
