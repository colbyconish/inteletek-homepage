#include "MainController.h"

void MainController::DefaultRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    auto resp=HttpResponse::newHttpViewResponse("home.csp", data);
    callback(resp);
}

void MainController::ProductsRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    data.insert("title", "Products");
    auto resp=HttpResponse::newHttpViewResponse("comingsoon.csp", data);
    callback(resp);
}

void MainController::AboutRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    data.insert("title", "About");
    auto resp=HttpResponse::newHttpViewResponse("comingsoon.csp", data);
    callback(resp);
}
