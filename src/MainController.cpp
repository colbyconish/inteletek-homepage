#include "MainController.h"
#include "Pages.hpp"

void MainController::DefaultRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    std::string path = req->getPath();
    if(path.size() <= 1) 
    {
        data.insert("page", Pages::Home);
        callback(HttpResponse::newHttpViewResponse("home.csp", data));
        return;
    }

    path.erase(0, 1);
    data.insert("page", from_string(path.c_str()));
    callback(HttpResponse::newHttpViewResponse(path + ".csp", data));
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

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);
}
