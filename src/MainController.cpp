#include "MainController.h"

void MainController::DefaultRoute(const HttpRequestPtr& req, 
		std::function<void (const HttpResponsePtr &)> &&callback) const
{	
    callback(HttpResponse::newFileResponse("/www/index.html");
}
