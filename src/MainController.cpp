#include "MainController.h"

void MainController::DefaultRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    auto resp = HttpResponse::newFileResponse("/www/index.html");	
    callback(resp);
}
