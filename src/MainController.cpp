#include <format>

#include <aws/sesv2/SESV2Client.h>
#include <aws/sesv2/model/SendEmailRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/auth/AWSCredentials.h>

#include "MainController.h"
#include "Pages.hpp"

using namespace std;
using namespace drogon;
using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::SESV2;
using namespace Aws::SESV2::Model;

void MainController::DefaultRoute(const HttpRequestPtr& req, 
    function<void (const HttpResponsePtr &)> &&callback) const
{	
    auto sub_path = req->path();
    if(sub_path.size() <= 1) 
        sub_path = "home";    
    else
        sub_path.erase(0, 1);

    Pages page{from_string(sub_path.c_str())};
    if(page == Pages::None) 
    {
        callback(HttpResponse::newNotFoundResponse());
        return;
    }

    HttpViewData data;
    data.insert("page", page);
    callback(HttpResponse::newHttpViewResponse(sub_path, data));
}

bool MainController::new_contact_inner(
    string &full_name,
    string &email,
    string &message)
{
    Content subject{};
    subject.SetData(string("New Contact - ") + full_name);

    Body body{};
    auto body_text = Content{};
    body_text.SetData(format(
        "This email is from the homepage web container.\n"
        "A new contact request:\n"
        "Name: {}\nEmail: {}\n\n{}\n",
        full_name, email, message
    ));
    body.SetText(body_text);

    // Create custom message
    Message mail_msg{};
    mail_msg.SetSubject(subject);
    mail_msg.SetBody(body);

    // Create email content
    EmailContent content{};
    content.SetSimple(mail_msg);

    Destination dest{};
    dest.AddToAddresses(TO_ADDRESS);

    // Create email request
    SendEmailRequest mail_req{};
    mail_req.SetFromEmailAddress(FROM_ADDRESS);
    mail_req.SetDestination(dest);
    mail_req.SetContent(content);

    ClientConfiguration config{};
    config.connectTimeoutMs = 1000;
    config.region = Region::US_EAST_1;

    // Get credentials
    DefaultAWSCredentialsProviderChain cred_provider;
    auto creds = cred_provider.GetAWSCredentials();

    // Send email
    SESV2Client client{creds, config};
    return client.SendEmail(mail_req).IsSuccess();
}

void MainController::NewContact(const HttpRequestPtr& req, 
    function<void (const HttpResponsePtr &)> &&callback,
    string &&full_name,
    string &&email,
    string &&message) const
{	
    auto success = new_contact_inner(full_name, email, message);

    // Verify response
    auto resp = HttpResponse::newHttpResponse();
    if(not success) resp->setStatusCode(k500InternalServerError);

    callback(resp);
}

void MainController::HealthCheck(const HttpRequestPtr& req, 
    function<void (const HttpResponsePtr &)> &&callback) const
{
    callback(HttpResponse::newHttpResponse());
}
