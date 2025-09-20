#include "MainController.h"
#include "Pages.hpp"

using namespace std;
using namespace drogon;

void MainController::DefaultRoute(const HttpRequestPtr& req, 
    function<void (const HttpResponsePtr &)> &&callback) const
{	
    HttpViewData data;
    string path = req->getPath();
    if(path.size() <= 1) 
    {
        data.insert("page", Pages::Home);
        callback(HttpResponse::newHttpViewResponse("home", data));
        return;
    }

    path.erase(0, 1);
    data.insert("page", from_string(path.c_str()));
    callback(HttpResponse::newHttpViewResponse(path, data));
}

void MainController::NewContact(const HttpRequestPtr& req, 
    function<void (const HttpResponsePtr &)> &&callback,
        string &&full_name,
        string &&email,
        string &&message) const
{	
    cout << "New Contact: " 
        << endl << full_name 
        << endl << email 
        << endl << message 
        << endl;

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);
}

void MainController::HealthCheck(const HttpRequestPtr& req, 
    function<void (const HttpResponsePtr &)> &&callback) const
{
    // Verify if request came from curl
    string header = req->getHeader("User-Agent");
    if(header.find("curl") != string::npos)
    {
        // Check health and return a status code
        callback(HttpResponse::newHttpResponse());
    }
    else
        callback(HttpResponse::newHttpViewResponse("notfound404"));
}
