#include <cstdlib>
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/Aws.h>

#include <json/json.h>

#include "MainController.h"

using namespace std;
using namespace aws::lambda_runtime;

invocation_response my_handler(invocation_request const& request)
{
    Json::Value data;
    Json::Reader reader;
    if(reader.parse(request.payload, data))
    {
        string full_name = data["fullname"].asString();
        string email = data["email"].asString();
        string message = data["message"].asString();
        
        bool ok = MainController::new_contact_inner(
            full_name, email, message
        );

        if(not ok)
            return invocation_response::failure(
                "{"
                    "\"isBase64Encoded\": false,"
                    "\"statusCode\": 500,"
                    "\"body\": \"SES call failed.\""
                "}"
                , 
                "application/json"
            );
    }
    else
        return invocation_response::failure(
            "{"
                "\"isBase64Encoded\": false,"
                "\"statusCode\": 500,"
                "\"body\": \"Json parsing failed.\""
            "}"
            , 
            "application/json"
        );

    return invocation_response::success("Success", "application/text");
}

int main()
{
    Aws::SDKOptions options{};
    Aws::InitAPI(options);

    run_handler(my_handler);

    Aws::ShutdownAPI(options);
    return EXIT_SUCCESS;
}
